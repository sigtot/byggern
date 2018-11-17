#include "motor.h"
#include "parameters.h"
#include "../lib/TWI_Master.h"
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "reference_state.h"
#include "control.h"

#define ENCODER_SCALE 17

// Motorbox pins
#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5   // Active low
#define RST PH6  // Active low

void MOTOR_Send_Voltage(unsigned char voltage) {
    unsigned char* msg = malloc(3 * sizeof(char));
    unsigned char addr = 0x50;
    msg[0] = addr;
    msg[1] = 0;
    msg[2] = voltage;

    _delay_us(50);
    TWI_Start_Transceiver_With_Data(msg, 3);
    free(msg);
}

void MOTOR_Init() {
    TWI_Master_Initialise();
    sei();
    // Set K port (MJ2) as input
    DDRK = 0x0;

    // Set pins in H port (MJ1) as output
    DDRH |= (1 << RST) |  // reset pin
            (1 << OE) |   // output enable pin
            (1 << EN) |   // enable pin
            (1 << SEL) |  // select high or low register pin
            (1 << DIR);   // motor direction pin

    // Set counter to 0
    PORTH &= ~(1 << RST);

    // Enable motor
    PORTH |= (1 << EN);

    // Enable encoder output
    PORTH &= ~(1 << OE);

    _delay_ms(10);

    motor_calibrate();
}

void motor_calibrate() {
    motor_set_direction(LEFT);
    MOTOR_Send_Voltage(120);
    _delay_ms(500);
    MOTOR_Send_Voltage(0);
    _delay_ms(500);
}

void motor_actuate(int16_t input) {
    if (input < 0) {
        motor_set_direction(LEFT);
        MOTOR_Send_Voltage(input);
    } else {
        motor_set_direction(RIGHT);
        MOTOR_Send_Voltage(input);
    }
}

int16_t motor_read_encoder() {
    volatile int16_t value = 0;
    // Enable output
    PORTH &= ~(1 << OE);

    // Select MSB
    PORTH &= ~(1 << SEL);

    _delay_ms(250);

    // Read MSB
    value |= (PINK << 8);

    // Select LSB
    PORTH |= (1 << SEL);

    _delay_us(250);

    // Read LSB
    value |= PINK;

    // Toggle reset
    if (PORTH & (1 << RST)) {
        PORTH &= ~(1 << RST);
    } else {
        PORTH |= (1 << RST);
    }

    // Disable output
    PORTH |= (1 << OE);

    return (-1) * value /
           ENCODER_SCALE;  // Return negative since direction is flipped
}

void motor_set_direction(MotorDir dir) {
    switch (dir) {
        case LEFT:
            PORTH &= ~(1 << DIR);
            break;
        case RIGHT:
            PORTH |= (1 << DIR);
    }
    _delay_us(100);
}
