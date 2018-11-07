#include "motorbox.h"
#include "../common/CAN_driver.h"
#include <avr/io.h>
#include "../common/can_ids.h"

void node2_send_servo(int servo_val) {
    Message message;
    message.ID = CAN_ID_SERVO;
    message.data[0] = servo_val;
    message.length = 1;
    CAN_Message_Send(&message);
    printf("Sent servo val %d with id %d and length %d\n\r",
        message.data[0], message.ID, message.length);
}

void node2_send_motor(int motor_val) {
    Message message;
    message.ID = CAN_ID_MOTOR;
    message.data[0] = motor_val;
    message.length = 1;
    CAN_Message_Send(&message);
    printf("Sent motor val %d with id %d and length %d\n\r",
        message.data[0], message.ID, message.length);
}
