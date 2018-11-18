#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "reference_state.h"
#include "motor.h"
#include "control.h"
#include "timer.h"

int main() {
    sei();
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);
    printf("CAN receive Solenoid signal test\n\r");
    solenoid_init();
    can_api_init();
    servo_init();
    motor_init();
    timer_init();

    while (1) {
        _delay_ms(1);
        if (_timer_flag_SHOULD_CALC_INPUT) {
            controller_calculate_and_actuate();
            _timer_flag_SHOULD_CALC_INPUT = 0;
        }
    }
    return 0;
}
