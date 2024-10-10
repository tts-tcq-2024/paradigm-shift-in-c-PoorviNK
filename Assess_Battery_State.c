#include <stdio.h>

// Define constants for limits and tolerances
#define TEMP_MAX_LIMIT 60.0         // Example temperature upper limit in °C
#define SOC_MAX_LIMIT 100.0         // Example state of charge upper limit in %
#define CHARGE_RATE_MAX_LIMIT 10.0   // Example charge rate upper limit in A

#define TEMP_WARNING_BUFFER 5.0      // Tolerance for temperature warning
#define SOC_WARNING_BUFFER 5.0        // Tolerance for state of charge warning
#define CHARGE_RATE_WARNING_BUFFER 1.0 // Tolerance for charge rate warning

// Flags for enabling/disabling warnings
int temp_warning_enabled = 1;
int soc_warning_enabled = 1;
int charge_rate_warning_enabled = 1;

int is_value_within_range(float value, float lower_bound, float upper_bound, const char* error_message) {
    if (value < lower_bound || value > upper_bound) {
        printf("%s out of range!\n", error_message);
        return 0;
    }
    return 1;
}

void issue_warning(float current_value, float max_limit, float warning_buffer, int enable_warning, const char* warning_message) {
    // Calculate if warning condition is met
    int should_issue_warning = enable_warning * (current_value >= max_limit - warning_buffer) * (current_value <= max_limit);
    // Print warning if conditions are met
    if (should_issue_warning) {
        printf("Warning: %s\n", warning_message);
    }
}

int assess_temperature(float temperature) {
    if (!is_value_within_range(temperature, 0, TEMP_MAX_LIMIT, "Temperature")) {
        return 0;
    }
    issue_warning(temperature, TEMP_MAX_LIMIT, TEMP_WARNING_BUFFER, temp_warning_enabled, "Approaching temperature peak!");
    return 1;
}

int assess_soc(float state_of_charge) {
    if (!is_value_within_range(state_of_charge, 20, SOC_MAX_LIMIT, "State of Charge")) {
        return 0;
    }
    issue_warning(state_of_charge, 20, SOC_WARNING_BUFFER, soc_warning_enabled, "Approaching discharge!");
    issue_warning(state_of_charge, SOC_MAX_LIMIT, SOC_WARNING_BUFFER, soc_warning_enabled, "Approaching charge peak!");
    return 1;
}

int assess_charge_rate(float charge_rate) {
    if (!is_value_within_range(charge_rate, 0, CHARGE_RATE_MAX_LIMIT, "Charge Rate")) {
        return 0;
    }
    issue_warning(charge_rate, CHARGE_RATE_MAX_LIMIT, CHARGE_RATE_WARNING_BUFFER, charge_rate_warning_enabled, "Approaching charge rate peak!");
    return 1;
}

int is_battery_status_ok(float temperature, float state_of_charge, float charge_rate) {
    return assess_temperature(temperature) && assess_soc(state_of_charge) && assess_charge_rate(charge_rate);
}

int main() {
    // Example values to check
    float current_temperature = 55.0; // Example temperature in °C
    float current_soc = 19.0;         // Example state of charge in %
    float current_charge_rate = 9.0;   // Example charge rate in A

    if (is_battery_status_ok(current_temperature, current_soc, current_charge_rate)) {
        printf("Battery is okay.\n");
    } else {
        printf("Battery conditions are not optimal.\n");
    }

    return 0;
}
