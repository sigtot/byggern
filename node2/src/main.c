#include "parameters.h"
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "PWM.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/delay.h>

#include "../../common/src/can.h"
#include "../../common/src/MCP2515.h"
#include "../../common/src/SPI.h"

#include "uart_api.h"
#include "can_api.h"
#include "reference_state.h"
#include "ir.h"
#include "game.h"
#include "../lib/TWI_Master.h"
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

    sei();
	UART_Init(MYUBRR);
	uart_api_enable();
	fdevopen(*UART_Transmit,NULL); // Transmit handled sequentially, receive with interrupt
	printf("Node 2 loves being ready -------------------\n\r");

    can_api_init();
	MOTOR_Init();
	control_init();

	while(1) {
        
	}

	return 0;
}
