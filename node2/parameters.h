#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define DDR_SPI DDRB
#define DD_SS DDB0
#define DD_SCK DDB1
#define DD_MOSI DDB2
#define DD_MISO DDB3
#define DD_CS DDB7
#define CS PB7
#define SEND PB2
#define RECEIVE PB3

#endif
