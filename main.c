#ifndef F_CPU
#define F_CPU 4915200
#endif
#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <util/delay.h>
#include <avr/io.h>
#include "led.h"
#include "driver.h"
#include "sram.h"


int main(){
	UART_Init(MYUBRR);
	fdevopen(*UART_Transmit, *UART_Receive);

	DDRA |= (1 << PA0);
	PORTA |= (1 << PA0);

	MCUCR |= (1 << SRE);// Enable externam memory interface

	SRAM_test();
	while(1){
		printf("Hello %s\n\r", "world");

			PORTA &= ~(1 << PA0);

		_delay_ms(200);

			PORTA |= (1 << PA0);
		_delay_ms(200);
	}

	return 0;
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
