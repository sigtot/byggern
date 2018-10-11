#ifndef F_CPU
#define F_CPU 4915200
#endif
#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "driver.h"
#include "sram.h"
#include "gal_test.h"
#include "adc.h"
#include <limits.h>
#include "oled.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "P_driver.h"


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
	//SRAM_test();
	oled_init();
	OLED_clear();
	/*for(int i = 0; i < 8; i++) {
		OLED_pos(i, 0);
		OLED_print("Hello world");
	}*/
	Nodeptr headptr = init_menu();
	Nodeptr selectedptr = headptr;


	while(1){
		Joy_state joy_state = joy_get_state();
		switch(joy_state.dir) {
			case DOWN:
				selectedptr = selectedptr->next;
				break;
			case UP:
				selectedptr = selectedptr->prev;
				break;
		}
		print_menu(headptr, selectedptr);
		_delay_ms(300);
	}




	return 0;
}
