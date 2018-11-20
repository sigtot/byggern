/**
 * @file uart.h
 * @brief UART driver for communication over serial line
 */
#ifndef UART_H
#define UART_H

/**
 * Initialization of baud rate, enabling communication
 * and setting frame format
 * @param baud Specify baudrate
 */
void UART_Init(unsigned int baud);

/**
 * Enables interrupts for the UART
 */
void UART_INT_Enable();

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
