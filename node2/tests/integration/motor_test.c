
#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "uart.h"
#include "reference_state.h"

#include "ir.h"

int main() {
	UART_Init(MYUBRR);
	fdevopen(*UART_Transmit,NULL);

	MOTOR_Init();
	sei();
	control_init();

	_delay_ms(500);

    printf("Testing motor: right of center -> left of center -> center\n\r");
	Set_motor_reference(150);
    _delay_ms(1000);
    Set_motor_reference(-150);
    _delay_ms(1000);
    Set_motor_reference(0);

    while(1);

	return 0;
}
