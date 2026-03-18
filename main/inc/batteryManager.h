#ifndef BATTERY_MANAGMENT_H_
#define BATTERY_MANAGMENT_H_

/* ADC and Voltage Calculation Constants */
#define ADC_MAX_RAW_VALUE           4095.0f // Max value for a 12-bit ADC
#define ADC_REF_VOLTAGE_MV          3100    // ADC reference voltage in millivolts
#define VOLTAGE_DIVIDER_FACTOR      2       // Factor for the battery voltage divider circuit

#define BATT_MV_THRESHOLD_100   3950 // Corresponds to a "full" battery
#define BATT_MV_THRESHOLD_80    3800
#define BATT_MV_THRESHOLD_60    3700
#define BATT_MV_THRESHOLD_40    3630
#define BATT_MV_THRESHOLD_20    3370

typedef enum {
    BATTERY_100 = 100,
    BATTERY_80  = 80,
    BATTERY_60  = 60,
    BATTERY_40  = 40,
    BATTERY_20  = 20
} battery_percent_t;

int init_battery(void);
int read_battery_millivolt(void);
battery_percent_t get_battery_percentage(void);

#endif // BATTERY_MANAGMENT_H_
