#ifndef BATTERY_CHECK_H
#define BATTERY_CHECK_H

// Early warning tolerance for all parameters (5% of upper limits)
#define TEMP_MAX_LIMIT 45.0
#define TEMP_WARNING_BUFFER (TEMP_MAX_LIMIT * 0.05)
#define SOC_MAX_LIMIT 80.0
#define SOC_WARNING_BUFFER (SOC_MAX_LIMIT * 0.05)
#define CHARGE_RATE_MAX_LIMIT 0.8
#define CHARGE_RATE_WARNING_BUFFER (CHARGE_RATE_MAX_LIMIT * 0.05)

// Flags for enabling/disabling warnings for specific parameters
extern int temp_warning_enabled;
extern int soc_warning_enabled;
extern int charge_rate_warning_enabled;

// Function prototypes
int assess_temperature(float temperature);
int assess_soc(float state_of_charge);
int assess_charge_rate(float charge_rate);
int is_battery_status_ok(float temperature, float state_of_charge, float charge_rate);

#endif
