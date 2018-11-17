

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
    fdevopen(*UART_Transmit, NULL);
    printf("starting receive motor test\n\r");
    can_api_init();
    MOTOR_Init();
    timer_init();

    while (1) {
        if (timer_flag_should_calculate_input()) {
            controller_calculate_and_actuate();
            timer_flag_finished_calculating_input();
        }
    }
    return 0;
}
