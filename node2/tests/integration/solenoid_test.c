#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/delay.h>
#include "uart.h"
#include "solenoid.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);
    printf("Starting solenoid test\n\r");
    solenoid_init();

    while (1) {
        solenoid_send_kick();
        _delay_ms(1000);
    }
    return 0;
}
