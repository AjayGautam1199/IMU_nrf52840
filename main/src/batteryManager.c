#include "config.h"
#include "batteryManager.h"
#include "peripherals.h"

#include <zephyr/drivers/adc.h>

LOG_MODULE_REGISTER(battery, LOG_LEVEL_INF);

/* ADC channel from devicetree: channel@4 (battery on AIN4 / P0.28) */
static const struct adc_dt_spec batt_adc = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 0);

int init_battery(void)
{
    return init_adc_channel(&batt_adc);
}

int read_battery_millivolt(void)
{
    int32_t raw_value = read_adc(&batt_adc);
    /* nRF52840 SAADC: gain 1/6, ref 0.6V internal => full scale 3.6V at 12-bit
     * raw_to_mv: (raw / 4095) * 3600 mV, then multiply by voltage divider factor */
    int32_t mv = (raw_value * 3600) / 4095;
    return mv * VOLTAGE_DIVIDER_FACTOR;
}

battery_percent_t get_battery_percentage(void)
{
    uint16_t mv = 0;
    for (uint8_t i = 0; i < 10; i++) {
        mv += read_battery_millivolt();
    }
    mv /= 10;
    LOG_INF("Battery: %d mV", mv);

    if (mv >= BATT_MV_THRESHOLD_100) return BATTERY_100;
    if (mv >= BATT_MV_THRESHOLD_80)  return BATTERY_80;
    if (mv >= BATT_MV_THRESHOLD_60)  return BATTERY_60;
    if (mv >= BATT_MV_THRESHOLD_40)  return BATTERY_40;
    return BATTERY_20;
}
