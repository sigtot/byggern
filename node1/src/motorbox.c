#include "motorbox.h"
#include <avr/io.h>
#include "../../common/src/can.h"
#include "../../common/src/can_ids.h"
#include <stdio.h>

void motorbox_send_servo_if_updated(int servo_val) {
    static int prev_val = 50;
    if (servo_val == prev_val) {
        return;
    }
    prev_val = servo_val;
    can_api_value_send(CAN_ID_SERVO, servo_val, 1);
}

void motorbox_send_motor_if_updated(int motor_val) {
    static int prev_val = 50;
    if (motor_val == prev_val) {
        return;
    }
    prev_val = motor_val;
    can_api_value_send(CAN_ID_MOTOR, motor_val, 1);
}

void motorbox_send_solenoid_if_kick(int button_val) {
    if (!button_val) {
        return;
    }
    can_api_value_send(CAN_ID_SOL, button_val, 1);
}
