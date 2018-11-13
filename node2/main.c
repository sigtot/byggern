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
#include "state.h"
#include "ir.h"
#include "game.h"
#include "TWI_Master.h"
#include "motor.h"
#include "control.h"

int main() {
	UART_Init(MYUBRR);
	UART_INT_Enable();
	fdevopen(*UART_Transmit,NULL); // Transmit handled sequentially, receive with interrupt
	printf("Node 2 loves being ready -------------------\n\r");

	CAN_Normal_Init();

	cli();
	EICRA &= ~(1 << ISC30); // Interrupt on falling edge
	EICRA |= (1 << ISC31); // Interrupt on falling edge
	EIMSK |= (1 << INT3); // Enable interrupt on INT3
	sei();
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);

	PWM_init();
	servo_set_pos(Get_servo_pos());

	MOTOR_Init();
	sei();
	control_init();
	while(1) {
		servo_set_pos(Get_servo_pos());
		MOTOR_Send_Voltage(1.5 * Get_servo_pos());
		printf("r = %d, x = %d\n\r", Get_motor_reference(), Get_motor_pos());
		_delay_ms(50);
	}
	ir_init();
	game_play_round();

	while(1); // Don't reset

	return 0;
}
