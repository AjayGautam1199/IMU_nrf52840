#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

/* Includes */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Zephyr APIs */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Forward declaration to avoid circular dependency */
struct IMUDataPacket;
#include "bleDriver.h"

/* BLE service configurations */
#define DEVICE_NAME "IMU_XIAO"

// --- UUID CONFIGURATION ---
#define IMU_SERVICE_UUID        0xfff2
#define IMU_CHARACTERISTIC_UUID 0xfff3
#define BATTERY_SERVICE_UUID    0x180F
#define BATTERY_CHARACTERISTIC_UUID 0x2A19

/* Defines */
#define USER_LED_DELAY_CONNECTION_STATE 1000
#define USER_LED_DELAY_ADVERTISING_STATE 300

// --- IMU Data Configuration ---
#define IMU_SAMPLE_RATE_MS 50  // How often we read/send IMU data (e.g., 20Hz)

// We send packets containing raw or processed IMU data
struct __attribute__((packed)) IMUData
{
    int16_t accel[3]; // Acceleration x,y,z (scaled x100 or raw)
    int16_t gyro[3];  // Gyro x,y,z (scaled x100 or raw)
    int8_t Step;
    int8_t WalkingVsRunning;
};
typedef struct IMUData IMU_data_t;

// The actual packet sent over BLE
struct __attribute__((packed)) IMUDataPacket
{
    uint32_t timestamp_ms; // System time in ms 4byte
    IMU_data_t data;       // The sensor reading 12 byte
};

#endif // CONFIG_H
