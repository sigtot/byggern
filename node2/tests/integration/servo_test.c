#include "parameters.h"
#include "uart.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void set_servo_and_wait(int servo_val) {
    printf("Setting servo to %d\n\r", servo_val);
    servo_set_pos(servo_val);
    _delay_ms(500);
}

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);

    servo_init();
    sei();

    while (1) {
        set_servo_and_wait(1);
        set_servo_and_wait(50);
        set_servo_and_wait(99);
        set_servo_and_wait(50);
    }

    return 0;
}
