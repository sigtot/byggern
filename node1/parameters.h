#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 4915200
#endif
#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

// Ports for SPI
#define DDR_SPI DDRB
#define DD_SS DDB4
#define DD_MOSI DDB5
#define DD_MISO DDB6
#define DD_SCK DDB7
#define DD_CS DDB4
#define CS PB4
#define SEND PB5
#define RECEIVE PB6

#endif
