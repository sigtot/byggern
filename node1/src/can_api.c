/**
 * @file can_api.h
 * @brief Sends CAN messages from Node 1
 */
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
            printf("Stop game\n\r");
            break;

        case CAN_ID_SCORE:
            printf("Score up 1\n\r");
            break;
    }
}

/**
 * Send message over CAN bus
 * @param ID one byte message ID
 * @param servo_val Data to be sendt
 * @param length Data length
 */
void can_api_value_send(char ID, int value, int length) {
    Message message;
    message.ID = ID;
    message.data[0] = value;
    message.length = length;
    CAN_Message_Send(&message);
}

/**
 * Initialization of CAN application programming interface
 * note: interrupts enabled on INT0
 */
void can_api_init() {
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
