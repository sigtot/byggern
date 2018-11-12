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
    //encoder_reset();
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

uint16_t read_encoder_value() {
    _delay_ms(10);
    volatile uint16_t value = 0;
    // Enable output
    PORTH &= ~(1 << OE);

    // Select MSB
    PORTH &= ~(1 << SEL);

    _delay_us(150);

    // Read MSB
    value |= (PORTK << 8);
    printf("PORTK MSB: %02x", PORTK);

    // Select LSB
    PORTH |=  (1 << SEL);

    _delay_us(150);

    // Read LSB
    value |= PORTK;
    printf("PORTK LSB: %02x", PORTK);

    // Toggle reset
    if (PORTH & (1 << RST)) {
        PORTH &= ~(1 << RST);
    } else {
        PORTH |= (1 << RST);
    }

    // Disable output
    PORTH |= (1 << OE);
    _delay_us(100);

    return value;
}

ISR(TIMER3_COMPA_vect)
{
    counter++;
    if (!(counter % 100)) {
        printf("Encoder value: %d\n\r", read_encoder_value());
        Set_motor_pos(30);
        if (!(counter % 400)) {
            control_set_motor_direction(LEFT);
		    Set_motor_pos(130);
            if (!(counter % 800)) {
                control_set_motor_direction(RIGHT);
    		    Set_motor_pos(130);
            }
        }
    }
}
