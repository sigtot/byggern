#include "control.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/delay.h>
#include "motor.h"
#include "state.h"
#include "parameters.h"

#define abs(x) ((x)<0 ? -(x) : (x))

static volatile uint16_t counter;
#define FREQ 800
static double timeStep = (1 / (double) FREQ);

// Motorbox pins
#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5 // Active low
#define RST PH6 // Active low

// Controller parameters
#define SCALE 30
#define K_P 1

void control_init_timer() {
    TCNT3 = 0; // Reset timer high register
    OCR3A = 0x2700; // About 408Hz

    // Enable CTC mode
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);

    TCCR3B |= (1 << CS31) | (1 << WGM32); // Set prescaler
    TIMSK3 |= (1 << OCIE3A); // Enable interrupts for TIMER3A
}

void encoder_reset() {
    PORTH &= ~(1 << RST);
    _delay_us(100);
    PORTH |= (1 << RST);
}

void control_init() {
    printf("PORTH before: %02x", PORTH);
    control_init_timer();
    // Set K port (MJ2) as input
    DDRK = 0x0;

    // Set pins in H port (MJ1) as output
    DDRH |= (1 << RST)| // reset pin
            (1 << OE) | // output enable pin
            (1 << EN) | // enable pin
            (1 << SEL)| // select high or low register pin
            (1 << DIR); // motor direction pin

    // Set counter to 0
    encoder_reset();

    // Enable motor
    PORTH |= (1 << EN);

    // Enable encoder output
    PORTH &= ~(1 << OE);
}

void control_set_motor_direction(MotorDir dir) {
    switch (dir) {
    case LEFT:
        PORTH &= ~(1 << DIR);
        break;
    case RIGHT:
        PORTH |= (1 << DIR);
    }
}

int16_t read_encoder_value() {
    volatile int16_t register_val = 0;
    // Enable output
    PORTH &= ~(1 << OE);

    // Select MSB
    PORTH &= ~(1 << SEL);

    _delay_us(20);

    // Read MSB
    register_val |= (PINK << 8);

    // Select LSB
    PORTH |=  (1 << SEL);

    _delay_us(20);

    // Read LSB
    register_val |= PINK;

    encoder_reset();

    // Disable output
    PORTH |= (1 << OE);

    return (-1) * register_val;
}

int calculate_input() {
    int err = Get_motor_reference() - Get_motor_pos();
    int mul = 1;
    if (abs(err) < MOTOR_MIN_VAL) {
        mul = MOTOR_MIN_VAL / err;
    }
    return K_P * err * mul;
}

void actuate_motor(int input) {
    if (input < 0) {
        control_set_motor_direction(LEFT);
        MOTOR_Send_Voltage((-1) * input);
    } else {
        control_set_motor_direction(RIGHT);
        MOTOR_Send_Voltage(input);
    }
}

ISR(TIMER3_COMPA_vect)
{
    counter++;
    if(!(counter % 20)) {
        int dx = read_encoder_value() * timeStep;
        Set_motor_pos(Get_motor_pos() + dx);
        if (!(counter % 10)) {
            actuate_motor(calculate_input());
        }
    }
}
