

#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "reference_state.h"
#include "motor.h"
#include "timer.h"
#include "control.h"

int main() {
    sei();
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);
    printf("starting receive motor test\n\r");
    can_api_init();
    MOTOR_Init();
    timer_init();

    int counter = 0;
    while (1) {
        if (_timer_flag_SHOULD_CALC_INPUT) {
            controller_calculate_and_actuate();
            _timer_flag_SHOULD_CALC_INPUT = 0;
        }
        _delay_ms(1);
    }
    return 0;
}
