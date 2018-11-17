#include "motorbox.h"
#include <avr/io.h>
#include "../../common/src/can.h"
#include "../../common/src/can_ids.h"
#include <stdio.h>

void motorbox_send_servo_if_updated(int servo_val) {
    static int prev_val = 50;
    if (servo_val == prev_val) {
        // printf("Not sending servo: %3d matches prev %3d\n\r", servo_val,
        // prev_val);
        return;
    }
    prev_val = servo_val;
    Message message;
    message.ID = CAN_ID_SERVO;
    message.data[0] = servo_val;
    message.length = 1;
    CAN_Message_Send(&message);
}

void motorbox_send_motor_if_updated(int motor_val) {
    static int prev_val = 50;
    if (motor_val == prev_val) {
        printf("Not sending motor: %3d matches prev %3d\n\r", motor_val,
               prev_val);
        return;
    }
    prev_val = motor_val;
    Message message;
    message.ID = CAN_ID_MOTOR;
    message.data[0] = motor_val;
    message.length = 1;
    CAN_Message_Send(&message);
}

void motorbox_send_solenoid_if_kick(int button_val) {
    if (!button_val) {
        printf("not sent button signal: %d\n\r", button_val);
        return;
    }
    Message message;
    message.ID = CAN_ID_SOL;
    message.data[0] = button_val;
    message.length = 1;
    CAN_Message_Send(&message);
}
