#ifndef CAN_API_H
#define CAN_API_H

void can_api_init();
void can_message_send(char ID, int servo_val, int length);

#endif
