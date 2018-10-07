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
	for(int i = 0; i < 8; i++) {
		OLED_pos(i, 0);
		OLED_print("Hello world");
	}

	return 0;
}
