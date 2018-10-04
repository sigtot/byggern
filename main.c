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
	while(1) {
		_delay_ms(100);
		oled_print_trash();
		oled_print_dollar();
		//adc_test();

		//printf("Button PB0: %d. Button: PB1: %d\n\r", !!(PINB & (1 << PB0)), !!(PINB & (1 << PB1)));
	}
	//print_hello_infinitely();


	return 0;
}

void print_hello_infinitely(){
	while(1){
		printf("Hello %s\n\r", "world");

			PORTA &= ~(1 << PA0);

		_delay_ms(200);

			PORTA |= (1 << PA0);
		_delay_ms(200);
	}
}

/*
int main(){
	led_init();

	while(1){
		//printf("%s", UART_Receive())
		led_turn_on();
		_delay_ms(20);
		led_turn_off();
		_delay_ms(20);
	}

	return 0;
}
*/
