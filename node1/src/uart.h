/**
 * @file uart.h
 * @brief UART driver for communication over serial line
 */

#ifndef UART_H
#define UART_H

/**
 * Initialization of baud rate, enabling communication
 * and setting frame format
 */
void UART_Init(unsigned int);

/**
 * Transmit a (unsigned) byte of data
 * @param data Data to be transmitted over serial interface
 */
void UART_Transmit(unsigned char data);

/**
 * Recieve a (unsigned) byte of data over serial interface
 */
unsigned char UART_Receive(void);

#endif
