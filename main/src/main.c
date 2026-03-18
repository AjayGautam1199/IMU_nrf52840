#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "config.h"
#include "peripherals.h"
#include "batteryManager.h"
#include "IMU.h"
#include "bleDriver.h"

LOG_MODULE_REGISTER(main_app, LOG_LEVEL_INF);

/* --- Thread Definitions --- */
#define LED_STACK_SIZE  1024
#define IMU_STACK_SIZE  4096
#define LED_PRIORITY    5
#define IMU_PRIORITY    5

K_THREAD_STACK_DEFINE(led_stack, LED_STACK_SIZE);
K_THREAD_STACK_DEFINE(imu_stack, IMU_STACK_SIZE);

static struct k_thread led_thread_data;
static struct k_thread imu_thread_data;

int main(void)
{
    LOG_INF("EMG_BETTR v2 starting on nRF52840...");

    /* 1. INITIALIZATION */
    init_led();
    init_battery();

    /* 2. START BLE (non-blocking on Zephyr, unlike NimBLE) */
    init_ble();

    /* 3. START THREADS */
    k_thread_create(&led_thread_data, led_stack, LED_STACK_SIZE,
                    user_led_thread, NULL, NULL, NULL,
                    LED_PRIORITY, 0, K_NO_WAIT);
    k_thread_name_set(&led_thread_data, "LED_thread");

    k_thread_create(&imu_thread_data, imu_stack, IMU_STACK_SIZE,
                    imu_task, NULL, NULL, NULL,
                    IMU_PRIORITY, 0, K_NO_WAIT);
    k_thread_name_set(&imu_thread_data, "IMU_Task");

    return 0;
}
