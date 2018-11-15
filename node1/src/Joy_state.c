#include "Joy_state.h"

int Joy_state_get_servo_value(Joy_state joy_state) {
    return (joy_state.x + 100) / 2;
}
