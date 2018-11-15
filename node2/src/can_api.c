#include "can_api.h"
#include "reference_state.h"
#include <avr/interrupt.h>
#include "../../common/src/can.h"
#include <avr/io.h>
#include "../../common/src/can_ids.h"
#include "servo.h"
#include <stdio.h>
#include <stdint.h>

static volatile int CAN_MSG_RECEIVED = 0;

static inline void handle_and_mutate() {
    Message message;
    CAN_Message_Receive(&message);
    switch (message.ID) {
    case CAN_ID_SERVO:
        Set_servo_reference(message.data[0]);
        servo_set_pos(message.data[0]);
        break;
    case CAN_ID_MOTOR:; //semicolon for obvious reasons (superessential)
        int val = message.data[0];
        if (val < 0) {
            val = 255 + val;
        }
        Set_motor_reference(val);
        break;
    case CAN_ID_SOL:
        if (message.data[0]) {
            solenoid_send_kick();
        }
        break;
    }
}

void can_api_init() {
	EICRA &= ~(1 << ISC30); // Interrupt on falling edge
	EICRA |= (1 << ISC31); // Interrupt on falling edge
	EIMSK |= (1 << INT3); // Enable interrupt on INT3
    CAN_Normal_Init();
}

ISR(INT3_vect) {
    while(CAN_MSG_RECEIVED); // Wait for any other messages to finish receiving
    CAN_MSG_RECEIVED = 1;
    handle_and_mutate();
    CAN_MSG_RECEIVED = 0;
}
