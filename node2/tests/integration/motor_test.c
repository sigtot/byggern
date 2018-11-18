#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "uart.h"
#include "reference_state.h"
#include "motor.h"
#include "control.h"
#include "timer.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);

    printf("Initiating and calibrating motor\n\r");
    motor_init();

    sei();
    timer_init();

    printf("Calibration finished, waiting 1 second\n\r");
    _delay_ms(1000);
    printf("Testing motor: right of center -> left of center -> center\n\r");

    int counter = 2000;
    int counter2 = 0;
    while (1) {
        if (_timer_flag_SHOULD_CALC_INPUT) {
            controller_calculate_and_actuate();
            _timer_flag_SHOULD_CALC_INPUT = 0;
        }

        if (!(counter % 2000)) {
            if (counter2 == 0) {
                printf("Setting reference to 150 (right)\n\r");
                Set_motor_reference(150);
            }
            if (counter2 == 40) {
                printf("Setting reference to -150 (left)\n\r");
                Set_motor_reference(50);
            }
            if (counter2 == 80) {
                printf("Setting reference to 0 (middle)\n\r");
                Set_motor_reference(100);
            }
            printf("Motor ref: %3d, pos: %3d\n\r", Get_motor_reference(),
                   Get_motor_pos());
            counter2++;
            if (counter2 == 120) {
                counter2 = 0;
            }
        }
        counter++;
    }

    while (1)
        ;
    return 0;
}
