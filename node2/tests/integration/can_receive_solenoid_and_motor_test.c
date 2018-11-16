

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
    printf("CAN receive Solenoid signal test\n\r");
	  can_api_init();
	  MOTOR_Init();
	  timer_init();
    solenoid_init();

    while(1) {
        _delay_ms(10);
        printf("Motor reference: %d\n\r", Get_motor_reference());
    }
	return 0;
}
