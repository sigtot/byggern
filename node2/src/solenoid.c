
#include "servo.h"
#include "PWM.h"
#include "parameters.h"
#include "solenoid.h"
#include <util/delay.h>

#include <avr/io.h>
#include <stdio.h>

void solenoid_init() {
    DDRE |= (1 << PE4);
    PORTE |= (1 << PE4);
}

void solenoid_send_kick(void) {
    printf("Sending kick\n\r");
    PORTE &= ~(1 << PE4);
    _delay_ms(60);
    PORTE |= (1 << PE4);
}
