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
#include <avr/interrupt.h>
#include <avr/sleep.h>

volatile uint8_t CAN_MSG_RECEIVED = 0;

ISR(INT0_vect) {
	CAN_MSG_RECEIVED = 1;
}

int main() {
	UART_Init(MYUBRR);
	fdevopen(*UART_Transmit, *UART_Receive);
	printf("Node 2 ready\n\r");

	CAN_Normal_Init();

	cli();
	EIMSK |= (1 << INT0); // Enable interrupt on INT0
	EICRA &= ~(1 << ISC00); // Interrupt on falling edge
	EICRA |= (1 << ISC01); // Interrupt on falling edge
	sei();
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);

	while(1) {
		if (CAN_MSG_RECEIVED) {
			CAN_MSG_RECEIVED = 0;
			joy_pos_receive();
		}
		sleep_enable();
	}

	return 0;
}
