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
    solenoid_init();
	  can_api_init();
	  MOTOR_Init();
	  timer_init();

    int counter = 0;
    int counter2 = 0;
    while(1) {
        if (timer_flag_should_calculate_input()) {
            controller_calculate_and_actuate();
            timer_flag_finished_calculating_input();
            counter2++;
        }
        counter++;
        if (counter % 100) {
            printf("Counters : %4d:%4d (diff: %3d) reference: %3d\n\r\n\r", counter, counter2, counter - counter2, Get_motor_reference());
        }
    }
	return 0;
}
