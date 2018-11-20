
#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "can_api.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);
    printf("CAN receive score signal test\n\r");
    can_api_init();
    sei();

    while (1) {
        _delay_ms(10);
    }
    return 0;
}
