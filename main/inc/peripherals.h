#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>

/* --- LED Functions --- */
int init_led(void);
void led_on(void);
void led_off(void);
void user_led_thread(void *p1, void *p2, void *p3);

/* --- ADC Functions --- */
typedef struct {
    const struct adc_dt_spec *spec;
} adc_config_t;

int init_adc_channel(const struct adc_dt_spec *spec);
int read_adc(const struct adc_dt_spec *spec);

#endif // PERIPHERALS_H
