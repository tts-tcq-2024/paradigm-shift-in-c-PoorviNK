#include <assert.h>
#include "battery_check.h"

int main() {
    // Test cases
    assert(is_battery_status_ok(25, 70, 0.7));  // No warnings or errors
    assert(!is_battery_status_ok(50, 85, 0));    // Out of range errors

    // Test early warning cases
    is_battery_status_ok(44, 21, 0.76);  // Should trigger warnings for all three parameters

    return 0;
}
