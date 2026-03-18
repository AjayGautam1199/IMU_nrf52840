#ifndef BLE_DRIVER_H
#define BLE_DRIVER_H

#include "config.h"

extern bool imu_notify_enabled;

void init_ble(void);
void send_imu_pkt(struct IMUDataPacket *pkt);

#endif // BLE_DRIVER_H
