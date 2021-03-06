/**
 * @file parameters.h
 * File contains necessary parameters
 * for atmega2560 pins, motor, servo, IR and PWM
 */

#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <avr/io.h>

// Clock frequencies
#ifndef F_CPU
#define F_CPU 16000000
#endif
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

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

// Motor
#define MOTOR_MIN_VAL 80
#define MOTOR_MAX_VAL 180
#define MOTOR_ZERO_TRESH 10

#define MOTOR_DEFAULT_KP 1
#define MOTOR_DEFAULT_KI 0.02
#define ERR_INTEGRAL_TRESH 5

#endif
