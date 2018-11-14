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
#include "../../lib/TWI_Master.h"
#include "motor.h"
#include "control.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
    (byte & 0x8000 ? '1' : '0'), \
    (byte & 0x4000 ? '1' : '0'), \
    (byte & 0x2000 ? '1' : '0'), \
    (byte & 0x1000 ? '1' : '0'), \
    (byte & 0x800 ? '1' : '0'), \
    (byte & 0x400 ? '1' : '0'), \
    (byte & 0x200 ? '1' : '0'), \
    (byte & 0x100 ? '1' : '0'), \
    (byte & 0x80 ? '1' : '0'), \
    (byte & 0x40 ? '1' : '0'), \
    (byte & 0x20 ? '1' : '0'), \
    (byte & 0x10 ? '1' : '0'), \
    (byte & 0x08 ? '1' : '0'), \
    (byte & 0x04 ? '1' : '0'), \
    (byte & 0x02 ? '1' : '0'), \
    (byte & 0x01 ? '1' : '0')

int main() {
	UART_Init(MYUBRR);
	uart_api_enable();
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
	servo_set_pos(Get_servo_reference());

	MOTOR_Init();
	sei();
	control_init();
	while(1) {
		servo_set_pos(Get_servo_reference());
		Set_motor_reference((Get_servo_reference() - 50) * 6);
	}
	ir_init();
	game_play_round();

	while(1); // Don't reset

	return 0;
}
