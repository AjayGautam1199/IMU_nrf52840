#include "config.h"
#include "bleDriver.h"

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

LOG_MODULE_REGISTER(ble_driver, LOG_LEVEL_INF);

/* --- State --- */
bool imu_notify_enabled = false;
static struct bt_conn *current_conn = NULL;

/* --- Battery Service --- */
static ssize_t read_battery_level(struct bt_conn *conn,
                                   const struct bt_gatt_attr *attr,
                                   void *buf, uint16_t len, uint16_t offset)
{
    uint8_t level = 80; // Replace with get_battery_percentage() when linked
    return bt_gatt_attr_read(conn, attr, buf, len, offset, &level, sizeof(level));
}

/* --- IMU CCC (Client Characteristic Configuration) changed callback --- */
static void imu_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
    imu_notify_enabled = (value == BT_GATT_CCC_NOTIFY);
    LOG_INF("IMU Notification %s", imu_notify_enabled ? "ENABLED" : "DISABLED");
}

/* --- GATT Service Definitions --- */

/* Battery Service (0x180F) */
BT_GATT_SERVICE_DEFINE(battery_svc,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_16(BATTERY_SERVICE_UUID)),
    BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_16(BATTERY_CHARACTERISTIC_UUID),
        BT_GATT_CHRC_READ,
        BT_GATT_PERM_READ,
        read_battery_level, NULL, NULL),
);

/* IMU Service (0xFFF2) */
BT_GATT_SERVICE_DEFINE(imu_svc,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_16(IMU_SERVICE_UUID)),
    BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_16(IMU_CHARACTERISTIC_UUID),
        BT_GATT_CHRC_NOTIFY,
        BT_GATT_PERM_NONE,
        NULL, NULL, NULL),
    BT_GATT_CCC(imu_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);

/* --- Advertising Data --- */
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL,
        BT_UUID_16_ENCODE(IMU_SERVICE_UUID)),
};

static const struct bt_data sd[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, sizeof(DEVICE_NAME) - 1),
};

/* --- Connection Callbacks --- */
static void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        LOG_ERR("Connection failed (err %u)", err);
        return;
    }
    LOG_INF("Connected");
    current_conn = bt_conn_ref(conn);
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    LOG_INF("Disconnected (reason %u)", reason);
    imu_notify_enabled = false;
    if (current_conn) {
        bt_conn_unref(current_conn);
        current_conn = NULL;
    }
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
};

/* --- Public API --- */
static void start_advertising(void)
{
    int err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err) {
        LOG_ERR("Advertising failed to start (err %d)", err);
    } else {
        LOG_INF("Advertising started");
    }
}

static void bt_ready(int err)
{
    if (err) {
        LOG_ERR("Bluetooth init failed (err %d)", err);
        return;
    }
    LOG_INF("Bluetooth initialized");
    start_advertising();
}

void init_ble(void)
{
    int err = bt_enable(bt_ready);
    if (err) {
        LOG_ERR("bt_enable failed (err %d)", err);
    }
}

void send_imu_pkt(struct IMUDataPacket *pkt)
{
    if (!imu_notify_enabled || !current_conn) {
        return;
    }
    bt_gatt_notify(current_conn, &imu_svc.attrs[1], pkt, sizeof(*pkt));
}
