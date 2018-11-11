#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <avr/io.h>

// Clock frequencies
#ifndef F_CPU
#define F_CPU 20000000
#endif
#define FOSC 20000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

// SPI ports
#define DDR_SPI DDRB
#define DD_SS DDB0
#define DD_SCK DDB1
#define DD_MOSI DDB2
#define DD_MISO DDB3
#define DD_CS DDB7
#define CS PB7
#define SEND PB2
#define RECEIVE PB3

// PWM frequency (Hz)
#define PWM_FREQ 50

// Servo
#define SERVO_DUTY_MIN 0.001
#define SERVO_DUTY_MAX 0.002

// IR
#define IR_BLOCK_THRESH 50
#define IR_FILTER_QUALITY 4

#endif
