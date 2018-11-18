#include "servo.h"
#include "PWM.h"
#include "parameters.h"

void servo_init() {
    PWM_init();
}

void servo_set_pos(int servo_pos) {
    // Map values 0-100 -> 0.001 -> 0.002
    double duty_cycle =
        (double)servo_pos *
            ((double)((double)SERVO_DUTY_MAX - (double)SERVO_DUTY_MIN)) /
            100.0 +
        (double)SERVO_DUTY_MIN;

    // Range guard (min 0.001 max 0.002)
    if (duty_cycle > SERVO_DUTY_MAX) {
        duty_cycle = SERVO_DUTY_MAX;
    }
    if (duty_cycle < SERVO_DUTY_MIN) {
        duty_cycle = SERVO_DUTY_MIN;
    }

    PWM_set_duty_cycle(duty_cycle);
}
