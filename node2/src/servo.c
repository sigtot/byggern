#include "servo.h"
#include "PWM.h"
#include "parameters.h"

void servo_init() {
    PWM_init();
}

void servo_set_pos(int servo_pos) {
    // Map values 0-100 -> 0.001 -> 0.002
    double duty_min = 0.001;
    double duty_max = 0.002;

    double duty_cycle =
        (double)servo_pos *
            ((double)((double)SERVO_DUTY_MAX - (double)SERVO_DUTY_MIN)) /
            100.0 +
        (double)SERVO_DUTY_MIN;

    // Range guard (min 0.001 max 0.002)
    if (duty_cycle > duty_max) {
        duty_cycle = duty_min;
        printf("dity cycle to large\n\r");
    }
    if (duty_cycle < duty_min) {
        duty_cycle = duty_min;
        printf("duty cycle to small\n\r");
    }
    printf("duty cycle: %d, duty_min: %d, duty_max: %d\n\r", duty_cycle, duty_min, duty_max);
    PWM_set_duty_cycle(duty_cycle);
}
