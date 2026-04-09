import sys
import asyncio
import json
import struct
import csv
import time
from datetime import datetime
from typing import List
from fastapi import FastAPI, WebSocket, WebSocketDisconnect, HTTPException
from fastapi.responses import HTMLResponse
from bleak import BleakScanner, BleakClient

# --- CONFIGURATION ---
IMU_SERVICE_UUID  = "0000fff2-0000-1000-8000-00805f9b34fb"
IMU_CHAR_UUID     = "0000fff3-0000-1000-8000-00805f9b34fb"
BATT_SERVICE_UUID = "0000180f-0000-1000-8000-00805f9b34fb"
BATT_CHAR_UUID    = "00002a19-0000-1000-8000-00805f9b34fb"

# BLE packet: <Ihhhhhhbb> = 18 bytes
# [uint32 timestamp][int16 ax,ay,az][int16 gx,gy,gz][int8 step][int8 walk_run]
PACKET_FORMAT = '<Ihhhhhhbb'
PACKET_SIZE   = struct.calcsize(PACKET_FORMAT)  # 18

app = FastAPI()

# --- GLOBAL STATE ---
connected_client: BleakClient = None
active_websockets: List[WebSocket] = []
battery_level = 0

# Step tracking: firmware sends rolling 0-127, we unwrap to true total
last_raw_step = 0
total_steps   = 0

# Recording state
is_recording = False
csv_file     = None
csv_writer   = None


def unwrap_step_count(raw_step: int) -> int:
    """
    Firmware sends step_count & 0x7F (rolling 0-127).
    Detect wrap-around and accumulate into a true total.
    """
    global last_raw_step, total_steps

    delta = (raw_step - last_raw_step) & 0x7F  # handles wrap from 127->0
    if delta > 0 and delta < 64:                # ignore big jumps (noise/reset)
        total_steps += delta
    last_raw_step = raw_step
    return total_steps


async def notify_callback(sender, data):
    """
    Callback for incoming BLE notifications.
    Packet (18 bytes): [Ts(4)][Ax(2)][Ay(2)][Az(2)][Gx(2)][Gy(2)][Gz(2)][Step(1)][WalkRun(1)]
    """
    global is_recording, csv_writer

    try:
        if len(data) < PACKET_SIZE:
            print(f"Short packet: {len(data)} bytes (expected {PACKET_SIZE})")
            return

        unpacked = struct.unpack(PACKET_FORMAT, data[:PACKET_SIZE])

        timestamp = unpacked[0]
        ax = unpacked[1] / 100.0
        ay = unpacked[2] / 100.0
        az = unpacked[3] / 100.0
        gx = unpacked[4] / 100.0
        gy = unpacked[5] / 100.0
        gz = unpacked[6] / 100.0
        raw_step = unpacked[7]
        walk_run = unpacked[8]  # 0=idle, 1=walking, 2=running

        steps = unwrap_step_count(raw_step)

        packet = {
            "time":  timestamp,
            "ax": ax, "ay": ay, "az": az,
            "gx": gx, "gy": gy, "gz": gz,
            "steps": steps,
            "walk_run": walk_run,
            "batt":  battery_level,
        }

        # Record to CSV
        if is_recording and csv_writer:
            csv_writer.writerow([timestamp, ax, ay, az, gx, gy, gz, steps, walk_run])

        # Broadcast to web clients
        message = json.dumps(packet)
        disconnected = []
        for ws in active_websockets:
            try:
                await ws.send_text(message)
            except Exception:
                disconnected.append(ws)
        for ws in disconnected:
            active_websockets.remove(ws)

    except Exception as e:
        print(f"Error processing packet: {e}")


# --- API ENDPOINTS ---

@app.get("/")
async def get():
    with open("index.html", "r") as f:
        return HTMLResponse(content=f.read(), status_code=200)


@app.get("/scan")
async def scan_devices():
    print("Scanning for devices...")
    devices = await BleakScanner.discover()
    return [{"name": d.name or "Unknown", "address": d.address} for d in devices]


@app.post("/connect/{address}")
async def connect_device(address: str):
    global connected_client, battery_level, last_raw_step, total_steps

    if connected_client and connected_client.is_connected:
        await connected_client.disconnect()

    try:
        connected_client = BleakClient(address)
        await connected_client.connect()
        print(f"Connected to {address}")

        # Reset step tracking on new connection
        last_raw_step = 0
        total_steps = 0

        try:
            batt_data = await connected_client.read_gatt_char(BATT_CHAR_UUID)
            battery_level = int(batt_data[0])
        except Exception as e:
            print(f"Could not read battery: {e}")
            battery_level = -1

        await connected_client.start_notify(IMU_CHAR_UUID, notify_callback)

        return {"status": "connected", "battery": battery_level}
    except Exception as e:
        print(f"Connection failed: {e}")
        raise HTTPException(status_code=500, detail=str(e))


@app.post("/disconnect")
async def disconnect_device():
    global connected_client
    if connected_client and connected_client.is_connected:
        await connected_client.disconnect()
        connected_client = None
    return {"status": "disconnected"}


@app.post("/record/start")
async def start_recording():
    global is_recording, csv_file, csv_writer

    if is_recording:
        return {"status": "already_recording"}

    try:
        filename = f"imu_data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
        csv_file = open(filename, mode='w', newline='')
        csv_writer = csv.writer(csv_file)
        csv_writer.writerow(["Timestamp", "Acc_X", "Acc_Y", "Acc_Z",
                             "Gyro_X", "Gyro_Y", "Gyro_Z", "Steps", "WalkRun"])

        is_recording = True
        print(f"Started recording to {filename}")
        return {"status": "started", "filename": filename}
    except Exception as e:
        print(f"Failed to start recording: {e}")
        raise HTTPException(status_code=500, detail=str(e))


@app.post("/record/stop")
async def stop_recording():
    global is_recording, csv_file, csv_writer

    if not is_recording:
        return {"status": "not_recording"}

    try:
        is_recording = False
        if csv_file:
            csv_file.close()
            csv_file = None
            csv_writer = None
        print("Stopped recording")
        return {"status": "stopped"}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.post("/steps/reset")
async def reset_steps():
    global total_steps, last_raw_step
    total_steps = 0
    last_raw_step = 0
    return {"status": "reset", "steps": 0}


@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    active_websockets.append(websocket)
    try:
        while True:
            await websocket.receive_text()
    except WebSocketDisconnect:
        active_websockets.remove(websocket)


if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)