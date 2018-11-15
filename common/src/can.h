#ifndef CAN_H
#define CAN_H
#include <avr/io.h>

typedef struct message {
    unsigned int ID;
    char length;
    char data[8];
} Message;

void CAN_LoopBack_Init();

void CAN_Normal_Init();

void CAN_Message_Send(Message *message);

void CAN_Transmit_Complete();

void CAN_Data_Receive();

void CAN_INT_Enable();

#endif
