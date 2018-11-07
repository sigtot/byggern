#ifndef UART_H
#define UART_H

void UART_Init(unsigned int baud);

void UART_INT_Enable();

void UART_Transmit(unsigned char data);

unsigned char UART_Receive(void);

#endif
