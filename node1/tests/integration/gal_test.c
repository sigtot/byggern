#include "parameters.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#define WAIT_TIME 10000

int main() {
    UART_Init(MYUBRR);
	fdevopen(*UART_Transmit, *UART_Receive);

    printf("======== Gal Test ========\n\r");
    DDRC |= (1 << PC2) | (1 << PC3);

    printf("Testing ram_cs for 10 seconds: (expecting LOW on P19)...\n\r");
    PORTC |= (1 << PC3);
    PORTC |= (1 << PC2);
    _delay_ms(WAIT_TIME / 2);
    PORTC &= ~(1 << PC2);
    _delay_ms(WAIT_TIME / 2);

    printf("Testing adc_cs for 10 seconds: (expecting LOW on P18)...\n\r");
    PORTC &= ~(1 << PC3);
    PORTC |= (1 << PC2);
    _delay_ms(2 * WAIT_TIME);

    printf("Testing oled_cs for 10 seconds: (expecting LOW on P17)...\n\r");
    PORTC &= ~(1 << PC3);
    PORTC &= ~(1 << PC2);
    _delay_ms(2 * WAIT_TIME);

    printf("===== Test Completed =====\n\r");
    while(1);
    return 0;
}
