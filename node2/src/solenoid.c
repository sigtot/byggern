
#include "servo.h"
#include "PWM.h"
#include "parameters.h"
#include "solenoid.h"
#include <util/delay.h>

#include <avr/io.h>
#include <stdio.h>

//TODO Må finne en pinne på node2 som kan trekke lavt med kretsen tilkoblet

void solenoid_init() {
    DDRE |= (1 << PE4);
    PORTE |= (1 << PE4);
}

void solenoid_send_kick(void) {
    PORTE &= ~(1 << PE4);
    _delay_ms(1);
    PORTE |= (1 << PE4);
}
