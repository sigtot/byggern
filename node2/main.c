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
#include "game.h"
#include "TWI_Master.h"
#include "motor.h"

int main() {
	UART_Init(MYUBRR);
	UART_INT_Enable();
	fdevopen(*UART_Transmit,NULL); // Transmit handled sequentially, receive with interrupt
	printf("Node 2 loves being ready -------------------\n\r");

	CAN_Normal_Init();

	cli();
	EIMSK |= (1 << INT0); // Enable interrupt on INT0
	EICRA &= ~(1 << ISC00); // Interrupt on falling edge
	EICRA |= (1 << ISC01); // Interrupt on falling edge
	//sei();
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);

	PWM_init();

	MOTOR_Init();
	sei();
	while(1) {
		_delay_ms(300);
		MOTOR_Send_Voltage(0x20);
	}
	ir_init();
	game_play_round();

	while(1); // Don't reset

	return 0;
}
