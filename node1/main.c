#define ACK 0x7E

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
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

#include "parameters.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "uart.h"
#include "sram.h"
#include "gal_test.h"
#include "adc.h"
#include <limits.h>
#include "oled.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "multifunction.h"
#include "Joy_state.h"
#include "motorbox.h"
#include "../common/can_ids.h"

#include "../common/SPI.h"
#include "../common/MCP2515.h"
#include "../common/CAN_driver.h"

int main(){
	UART_Init(MYUBRR);
	fdevopen(*UART_Transmit, *UART_Receive);
	printf("Starting up...\n\r");

	DDRA |= (1 << PA0);
	PORTA |= (1 << PA0);

	//GAL_test();
	//MCUCR |= (1 << SRE);// Enable external memory interface
/*
	//Interrupt Enable
	GICR |= (1 << INT0);
	sei();
	MCUCR |= (1 << ISC00);
	MCUCR &= ~(1 << ISC01);
	DDRD &= ~(1 << PD2);
*/
	SRAM_test();
	oled_init();
	OLED_clear();
    CAN_Normal_Init();

    joy_print_state();
    //joy_pos_send(joy_get_state());
    node2_send_servo(77);






	//char c = SPI_SlaveReceive();
	//printf("Recieved: %c ("BYTE_TO_BINARY_PATTERN")\n\r", c, BYTE_TO_BINARY(c));



	Nodeptr headptr = init_menu();
	Nodeptr selectedptr = headptr;

	int should_update_menu = 1;
	while(1){
		Joy_state joy_state = joy_get_state();
		switch(joy_state.dir) {
		case DOWN:
			if (selectedptr->next != NULL) {
				selectedptr = selectedptr->next;
				should_update_menu = 1;
			}
			break;
		case UP:
			if (selectedptr->prev != NULL) {
				selectedptr = selectedptr->prev;
				should_update_menu = 1;
			}
			break;
		case RIGHT:
			if (selectedptr->child != NULL) {
				headptr = selectedptr->child;
				selectedptr = selectedptr->child;
				should_update_menu = 1;
			}
			break;
		case LEFT:
			if (selectedptr->parent != NULL) {
				headptr = selectedptr->parent;
				selectedptr = selectedptr->parent;
				should_update_menu = 1;
			}
			break;
		}

		Button button_state = buttons_get_state();
		if (button_state.joy && (selectedptr->child != NULL)) {
			headptr = selectedptr->child;
			selectedptr = selectedptr->child;
			should_update_menu = 1;
		}

		if (should_update_menu) {
			print_menu(headptr, selectedptr);
			_delay_ms(300);
			should_update_menu = 0;
		}
	}




	return 0;
}
