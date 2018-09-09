#ifndef DRIVER_H
#define DRIVER_H

void UART_Init(unsigned int);

void UART_Transmit(unsigned char data);

unsigned char UART_Receive(void);

#endif
