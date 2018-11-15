

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

	PWM_init();
	sei();

    printf("setting servo\n\r");
    servo_set_pos(1);
    _delay_ms(300);
    servo_set_pos(1);
    _delay_ms(300);
    servo_set_pos(0);

    while(1);

	return 0;
}
