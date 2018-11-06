#include "../common/CAN_driver.h"
#include <avr/io.h>
#include "joy_pos_sender.h"

void __encode(Joy_state joy_state, Message *encoded_msg) {
    encoded_msg->data[0] = (char) joy_state.x;
    encoded_msg->data[1] = (char) joy_state.y;
    encoded_msg->data[2] = (char) joy_state.dir;
    encoded_msg->length = 3;
}

void joy_pos_send(Joy_state joy_state) {
    Message message;
    __encode(joy_state, &message);
    message.ID = 1;
    CAN_Message_Send(&message);
    printf("Sent joy data with length \n\r", message.length);
}
