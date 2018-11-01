#ifndef F_CPU
#define F_CPU 16000000
#endif
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include "uart.h"
#include "CAN_driver.h"
#include "MCP2515.h"
#include "SPI.h"
#include "MCP2515.h"

int main() {
	UART_Init(MYUBRR);
	fdevopen(*UART_Transmit, *UART_Receive);
	printf("Node 2 ready\n\r");
/*
	CAN_LoopBack_Init();
	MCP2515_Write(0x00,'b');
	printf("Wrote char\n\r");
	char c = MCP2515_Read(0x00);
	printf("Received char %c\n\r", c);

	printf("CAN initiated in loopback mode\n\r");
	Message message;
    message.data[0] = 'N';
    message.data[1] = 'o';
    message.data[2] = 'd';
    message.data[3] = 'e';
    message.data[4] = ' ';
    message.data[5] = '2';
    message.data[6] = '!';
    message.ID = 1;
    message.length = 0x4;
    CAN_Message_Send(&message);
	printf("Message sent\n\r");
    char msg[9];
    CAN_Data_Receive(&msg);
    printf("Message received: %s\n\r", msg);*/

	CAN_Normal_Init();
	char msg[9];
	while(!(MCP_CANINTF & (1 << MCP_RX1IF)));
	CAN_Data_Receive(&msg);
    printf("Message received: %s\n\r", msg);
	while(1);
	return 0;
}
