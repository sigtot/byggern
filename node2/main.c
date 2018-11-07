#include "parameters.h"
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "PWM.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/delay.h>

#include "../common/CAN_driver.h"
#include "../common/MCP2515.h"
#include "../common/SPI.h"

#include "uart_api.h"
#include "reference_state.h"

volatile uint8_t CAN_MSG_RECEIVED = 0;

ISR(INT0_vect) {
	CAN_MSG_RECEIVED = 1;
}

int main() {
	UART_Init(MYUBRR);
	UART_INT_Enable();
	fdevopen(*UART_Transmit,NULL);
	printf("Node 2 ready\n\r");
	printf("Node 2 loves being ready\n\r");

	cli();
	sei();
	printf("Sei alright\n\r");
	while(1) {
		_delay_ms(1000);
		printf("Servo pos: %d, Motor pos: %d\n\r", Get_servo_pos(), Get_motor_pos());
	}
	char buf[100];
	while(1) {
		gets(&buf);
		printf("Read string %s\n\r", buf);
	}

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

	PWM_init();

	while(1);

	return 0;
}
