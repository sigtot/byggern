#include "parameters.h"
#include "timer.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "uart.h"
#include "reference_state.h"
#include "motor.h"
#include "control.h"

int main() {
	UART_Init(MYUBRR);
	fdevopen(*UART_Transmit,NULL);

	printf("Starting motor voltage test...\n\r");
  printf("Initiating motor\n\r");
	MOTOR_Init();

	printf("Initial calibration finished, waiting 1 second\n\r");
	_delay_ms(1000);

    int wait = 2;
    while(1) {
        for (int v = 30; v <= 200; v += 10) {
            printf("Moving right with voltage %d\n\r", v);
            motor_set_direction(RIGHT);
            MOTOR_Send_Voltage(v);
            _delay_ms(1000);
            printf("Recalibrating motor and waiting %d seconds...\n\r", wait);
            motor_calibrate();
            _delay_ms(wait * 3000);
        }
    }


	return 0;
}

int counter = 0;