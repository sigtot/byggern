#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include "led.h"
#include "driver.h"

int main(){
	UART_Init ();

	while(1){
		//printf("%s", UART_Receive())
		UART_Transmit('d');
		_delay_ms(1000);
	}

	return 0;
}
