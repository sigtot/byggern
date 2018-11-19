#include "can_api.h"
#include <avr/interrupt.h>
#include "../../common/src/can.h"
#include <avr/io.h>
#include "../../common/src/can_ids.h"
#include <stdio.h>
#include <stdint.h>

static volatile int CAN_MSG_RECEIVED = 0;

static inline void handle_and_mutate() {
    Message message;
    CAN_Message_Receive(&message);
    switch (message.ID) {
        case CAN_ID_STOP_GAME:

        case CAN_ID_SCORE:
            printf("Score up 1\n\r");
    }
}

void can_api_value_send(char ID, int value, int length) {
    Message message;
    message.ID = ID;
    message.data[0] = value;
    message.length = length;
    CAN_Message_Send(&message);
}

void can_api_init() {
    /**
     * Set interrupt on falling edge for INT0
     * Enable interrupt on INT0
     */
    MCUCR &= ~(1 << ISC00);
    MCUCR |= (1 << ISC01);
    GICR |= (1 << INT0);
    CAN_Normal_Init();
}

ISR(INT0_vect) {
    // Wait for any other messages to finish receiving
    while (CAN_MSG_RECEIVED)
        ;
    CAN_MSG_RECEIVED = 1;
    handle_and_mutate();
    CAN_MSG_RECEIVED = 0;
}
