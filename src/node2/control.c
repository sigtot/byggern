#include "control.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/delay.h>
#include "motor.h"
#include "reference_state.h"

static volatile uint16_t counter;
#define FREQ 408
static double timeStep = (1 / (double) FREQ);

// Motorbox pins
#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5 // Active low
#define RST PH6 // Active low

void control_init_timer() {
    TCNT3 = 0; // Reset timer high register
    OCR3A = 0x1337; // About 408Hz
    // Enable CTC mode
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);

    TCCR3B |= (1 << CS31) | (1 << WGM32);
    TIMSK3 |= (1 << OCIE3A); // Enable interrupts for TIMER3A
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
    PORTH &= ~(1 << RST);
    printf("PORTH after: %02x", PORTH);

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
    volatile int16_t value = 0;
    // Enable output
    PORTH &= ~(1 << OE);

    // Select MSB
    PORTH &= ~(1 << SEL);

    _delay_us(250);

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

    return (-1) * value; // Return negative since direction is flipped
}

ISR(TIMER3_COMPA_vect)
{
    counter++;
    if (!(counter % 100)) {
        int16_t motor_val = read_encoder_value();
        Set_motor_pos(Get_motor_pos() + motor_val);
    }

    if (!(counter % FREQ)) {
        printf("Motor pos: %d\n\r", Get_motor_pos());
    }
}
