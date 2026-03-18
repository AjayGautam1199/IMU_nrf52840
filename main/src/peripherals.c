#include "peripherals.h"
#include "config.h"

LOG_MODULE_REGISTER(peripherals, LOG_LEVEL_INF);

/* LED from devicetree alias led0 */
static const struct gpio_dt_spec user_led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

/* ------------------------------ LED Functions ----------------------------- */
int init_led(void)
{
    if (!gpio_is_ready_dt(&user_led)) {
        LOG_ERR("LED device not ready");
        return -ENODEV;
    }
    return gpio_pin_configure_dt(&user_led, GPIO_OUTPUT_INACTIVE);
}

void led_on(void)
{
    gpio_pin_set_dt(&user_led, 1);
}

void led_off(void)
{
    gpio_pin_set_dt(&user_led, 0);
}

/* ------------------------------ ADC Functions ----------------------------- */
int init_adc_channel(const struct adc_dt_spec *spec)
{
    if (!adc_is_ready_dt(spec)) {
        LOG_ERR("ADC device not ready");
        return -ENODEV;
    }
    return adc_channel_setup_dt(spec);
}

int read_adc(const struct adc_dt_spec *spec)
{
    int16_t buf;
    int err;
    struct adc_sequence sequence = {
        .buffer = &buf,
        .buffer_size = sizeof(buf),
    };

    err = adc_sequence_init_dt(spec, &sequence);
    if (err) {
        LOG_ERR("ADC sequence init failed (err %d)", err);
        return 0;
    }

    err = adc_read_dt(spec, &sequence);
    if (err) {
        LOG_ERR("ADC read failed (err %d)", err);
        return 0;
    }

    return (int)buf;
}

/* ----------------------------- User LED Thread ---------------------------- */
void user_led_thread(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while (1) {
        led_off();
        k_msleep(1000);
        led_on();
        k_msleep(1000);
    }
}
