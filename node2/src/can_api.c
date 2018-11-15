#include "can_api.h"
#include "reference_state.h"
#include <avr/interrupt.h>
#include "../../common/src/CAN_driver.h"
#include <avr/io.h>
#include "../../common/src/can_ids.h"
#include "servo.h"

volatile int CAN_MSG_RECEIVED = 0;

static inline void handle_and_mutate() {
    Message message;
    CAN_Message_Receive(&message);
    switch (message.ID) {
    case CAN_ID_SERVO:
        Set_servo_reference(message.data[0]);
        servo_set_pos(message.data[0]);
        break;
    case CAN_ID_MOTOR:
        Set_motor_reference(message.data[0]);
        break;
    }
}

ISR(INT3_vect) {
    while(CAN_MSG_RECEIVED); // Wait for any other messages to finish receiving
	CAN_MSG_RECEIVED = 1;
    handle_and_mutate();
    CAN_MSG_RECEIVED = 0;
}
