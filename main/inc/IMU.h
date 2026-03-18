#ifndef IMU_H
#define IMU_H

#include "config.h" // Includes definition of IMU_data_t

// I2C Address for MPU6500 (Usually 0x68 or 0x69)
#define IMU_ADDRESS 0x68

/**
 * @brief Initializes the I2C driver and the MPU6500 sensor.
 * @return 0 on success, non-zero error code on failure.
 */
int imu_init(void);

/**
 * @brief Polls the MPU6500 for the latest Accelerometer and Gyroscope data.
 * @return IMU_data_t Struct containing Accel[3] and Gyro[3] values.
 */
IMU_data_t imu_read(void);

/**
 * @brief Zephyr thread entry for IMU polling and BLE transmission.
 */
void imu_task(void *p1, void *p2, void *p3);

#endif // IMU_H
