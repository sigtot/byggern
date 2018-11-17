#include <avr/io.h>
#define FOSC 4915200  // Clock Speed
#define BAUD 9600

void UART_Init(unsigned int ubrr) {
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void UART_INT_Enable() {
    UCSR0B |= (1 << RXCIE0);
}

void UART_Transmit(unsigned char data) {
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char UART_Receive(void) {
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;
    /* Get and return received data from buffer */
    return UDR0;
}
