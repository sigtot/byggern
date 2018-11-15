

#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "uart.h"
#include "reference_state.h"
#include "motor.h"
#include "control.h"


int main() {

    sei();
	UART_Init(MYUBRR);
	fdevopen(*UART_Transmit,NULL);
    printf("starting receive motor test\n\r");
	can_api_init();
	MOTOR_Init();
	control_init();

	while(1) {
        _delay_ms(100);
        printf("motor reference: %d\n\r", Get_motor_reference());
    }
	return 0;
}
