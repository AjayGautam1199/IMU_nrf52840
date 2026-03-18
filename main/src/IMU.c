#include "IMU.h"
#include "IMU/driver_mpu6500_basic.h"
#include "bleDriver.h"
#include "config.h"

LOG_MODULE_REGISTER(imu_task_mod, LOG_LEVEL_INF);

int imu_init(void)
{
    LOG_INF("Initializing MPU6500...");

    uint8_t res = mpu6500_basic_init(MPU6500_INTERFACE_IIC, 0x68);

    if (res != 0) {
        LOG_ERR("MPU6500 Initialization Failed! Error Code: %d", res);
        return res;
    }

    LOG_INF("MPU6500 initialized successfully!");
    return 0;
}

IMU_data_t imu_read(void)
{
    IMU_data_t imu_sample;
    float g[3], dps[3];

    if (mpu6500_basic_read(g, dps) != 0) {
        LOG_WRN("Failed to read sensor data");
        memset(&imu_sample, 0, sizeof(imu_sample));
        return imu_sample;
    }

    // Convert float to int16 for transmission to save bandwidth
    for (int i = 0; i < 3; i++) {
        imu_sample.accel[i] = (int16_t)(g[i] * 100);
        imu_sample.gyro[i]  = (int16_t)(dps[i] * 100);
    }
    return imu_sample;
}

void imu_task(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    k_msleep(100); // Let power stabilize
    LOG_INF("Starting IMU Task...");

    if (imu_init() != 0) {
        LOG_ERR("IMU Init Failed! Task exiting...");
        return;
    }

    struct IMUDataPacket packet;

    while (1) {
        IMU_data_t raw_data = imu_read();

        packet.timestamp_ms = (uint32_t)k_uptime_get_32();
        packet.data = raw_data;

        LOG_INF("Ts:%u | Acc:(%d, %d, %d) | Gyro:(%d, %d, %d)",
                packet.timestamp_ms,
                raw_data.accel[0], raw_data.accel[1], raw_data.accel[2],
                raw_data.gyro[0],  raw_data.gyro[1],  raw_data.gyro[2]);

        send_imu_pkt(&packet);

        k_msleep(IMU_SAMPLE_RATE_MS);
    }
}
