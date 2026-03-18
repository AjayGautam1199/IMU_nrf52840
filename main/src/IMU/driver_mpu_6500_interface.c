/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 *
 * The MIT License (MIT)
 *
 * @file      driver_mpu6500_interface.c
 * @brief     driver mpu6500 interface source file (nRF52840 / Zephyr port)
 * @version   1.0.0
 * @author    Shifeng Li (ported to Zephyr by Ajay Gautam)
 * @date      2024-07-30
 */

#include "driver_mpu_6500_interface.h"
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(mpu6500_iface, LOG_LEVEL_INF);

/* Get I2C device from devicetree */
static const struct device *i2c_dev = NULL;

/**
 * @brief  interface iic bus init
 */
uint8_t mpu6500_interface_iic_init(void)
{
    i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));
    if (!device_is_ready(i2c_dev)) {
        LOG_ERR("I2C device not ready");
        return 1;
    }
    LOG_INF("I2C initialized successfully");
    return 0;
}

/**
 * @brief  interface iic bus deinit
 */
uint8_t mpu6500_interface_iic_deinit(void)
{
    return 0;
}

/**
 * @brief      interface iic bus read
 * @param[in]  addr iic device 7-bit address
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of the data buffer
 */
uint8_t mpu6500_interface_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (i2c_dev == NULL) {
        return 1;
    }
    int ret = i2c_burst_read(i2c_dev, addr, reg, buf, len);
    if (ret != 0) {
        LOG_ERR("I2C read failed (addr=0x%02X, reg=0x%02X, err=%d)", addr, reg, ret);
        return 1;
    }
    return 0;
}

/**
 * @brief     interface iic bus write
 * @param[in] addr iic device 7-bit address
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 */
uint8_t mpu6500_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (i2c_dev == NULL) {
        return 1;
    }
    int ret = i2c_burst_write(i2c_dev, addr, reg, buf, len);
    if (ret != 0) {
        LOG_ERR("I2C write failed (addr=0x%02X, reg=0x%02X, err=%d)", addr, reg, ret);
        return 1;
    }
    return 0;
}

/**
 * @brief  interface spi bus init
 */
uint8_t mpu6500_interface_spi_init(void)
{
    return 0;
}

/**
 * @brief  interface spi bus deinit
 */
uint8_t mpu6500_interface_spi_deinit(void)
{
    return 0;
}

/**
 * @brief      interface spi bus read
 */
uint8_t mpu6500_interface_spi_read(uint8_t reg, uint8_t *buf, uint16_t len)
{
    return 0;
}

/**
 * @brief     interface spi bus write
 */
uint8_t mpu6500_interface_spi_write(uint8_t reg, uint8_t *buf, uint16_t len)
{
    return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 */
void mpu6500_interface_delay_ms(uint32_t ms)
{
    k_msleep(ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 */
void mpu6500_interface_debug_print(const char *const fmt, ...)
{
    /* Intentionally left empty - use Zephyr LOG macros where needed */
}

/**
 * @brief     interface receive callback
 * @param[in] type irq type
 */
void mpu6500_interface_receive_callback(uint8_t type)
{
    switch (type) {
    case MPU6500_INTERRUPT_MOTION:
        LOG_DBG("mpu6500: irq motion");
        break;
    case MPU6500_INTERRUPT_FIFO_OVERFLOW:
        LOG_DBG("mpu6500: irq fifo overflow");
        break;
    case MPU6500_INTERRUPT_FSYNC_INT:
        LOG_DBG("mpu6500: irq fsync int");
        break;
    case MPU6500_INTERRUPT_DMP:
        LOG_DBG("mpu6500: irq dmp");
        break;
    case MPU6500_INTERRUPT_DATA_READY:
        LOG_DBG("mpu6500: irq data ready");
        break;
    default:
        LOG_DBG("mpu6500: irq unknown code");
        break;
    }
}

/**
 * @brief     interface dmp tap callback
 */
void mpu6500_interface_dmp_tap_callback(uint8_t count, uint8_t direction)
{
    LOG_DBG("mpu6500: tap irq direction=%d count=%d", direction, count);
}

/**
 * @brief     interface dmp orient callback
 */
void mpu6500_interface_dmp_orient_callback(uint8_t orientation)
{
    LOG_DBG("mpu6500: orient irq orientation=%d", orientation);
}
