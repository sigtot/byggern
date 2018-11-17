
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
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);

    printf("Initiating and calibrating motor\n\r");
    MOTOR_Init();

    sei();
    timer_init();

    printf("Calibration finished, waiting 1 second\n\r");
    _delay_ms(1000);
    printf("Testing motor: right of center -> left of center -> center\n\r");

    int counter = 2000;
    int counter2 = 0;
    while (1) {
        if (timer_flag_should_calculate_input()) {
            controller_calculate_and_actuate();
            timer_flag_finished_calculating_input();
        }

        if (!(counter % 2000)) {
            if (counter2 == 0) {
                printf("Setting reference to 150 (right)\n\r");
                Set_motor_reference(150);
            }
            if (counter2 == 200) {
                printf("Setting reference to -150 (left)\n\r");
                Set_motor_reference(-150);
            }
            if (counter2 == 400) {
                printf("Setting reference to 0 (middle)\n\r");
                Set_motor_reference(0);
            }
            if (!(counter2 % 100)) {
                printf("Motor ref: %3d, pos: %3d\n\r", Get_motor_reference(),
                       Get_motor_pos());
            }
            counter2++;
        }
        counter++;
    }

    while (1)
        ;
    return 0;
}
