
#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "reference_state.h"
#include "motor.h"
#include "control.h"

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

    Set_motor_reference(150);
    _delay_ms(1000);
    Set_motor_reference(-150);
    _delay_ms(1000);
    Set_motor_reference(0);

    while (1)
        ;

    return 0;
}
