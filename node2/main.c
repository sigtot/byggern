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
#include "can_api.h"
#include "reference_state.h"
#include "ir.h"

int main() {
	UART_Init(MYUBRR);
	UART_INT_Enable();
	fdevopen(*UART_Transmit,NULL); // Transmit handled sequentially, receive with interrupt
	printf("Node 2 loves being ready\n\r");

	cli();
	sei();

	CAN_Normal_Init();

	cli();
	EIMSK |= (1 << INT0); // Enable interrupt on INT0
	EICRA &= ~(1 << ISC00); // Interrupt on falling edge
	EICRA |= (1 << ISC01); // Interrupt on falling edge
	sei();
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);

	PWM_init();

	ir_init();

	while(1) {
		_delay_ms(10); // Using delay until we can set up a gameloop with timer.h
		servo_set_pos(Get_servo_pos());
		if (Ir_is_blocked()) {
			printf("IR is blocked!\n\r");
		}
		//printf("Servo pos: %d, Motor pos: %d\n\r", Get_servo_pos(), Get_motor_pos());


		// We can now sleep if we want;
		//sleep_enable();
	}


	while(1);

	return 0;
}
