#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "uart.h"
#include "../lib/TWI_Master.h"

int main() {
    DDRD |= (1 << PD0);
    PORTD &= ~(1 << PD0);

    sei();
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);
    printf("Starting TWI test\n\r");

    TWI_Master_Initialise();
    int counter = 0;
    while (1) {
        _delay_ms(5);
        unsigned char* msg = malloc(3 * sizeof(char));
        unsigned char addr = 0x50;
        msg[0] = addr;
        msg[1] = 0;
        msg[2] = counter % 256;

        TWI_Start_Transceiver_With_Data(msg, 3);
        free(msg);
        counter++;
        if (!(counter % 1000)) {
            printf("Sent %d messages\n\r", counter);
        }
    }
    return 0;
}
