
#include "timer.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "stdio.h"
#include "parameters.h"


static volatile uint16_t counter = 0;
int _timer_flag_SHOULD_CALC_INPUT = 0;

void timer_init() {

    //enable CTC
    TCCR1B &= ~(1 << WGM13);
    TCCR1B |= (1 << WGM12);
    TCCR1A &= ~(1 << WGM11);
    TCCR1A &= ~(1 << WGM10);

    TIMSK |= (1 << OCIE1A);

    uint16_t frequency = 100;
    uint16_t TOP = (F_CPU / (2*1024*frequency)) - 1;
    OCR1A = TOP;

    //TCCR1B = (TCCR1B & 0b11111000) | 0b001; //prescale = 1
    TCCR1B = (TCCR1B & 0b11111000) | 0b101;
    TCCR1B |= (1 << CS12);
    TCCR1B &= ~(1 << CS11);
    TCCR1B |= (1 << CS10);

    sei();
}
ISR(TIMER1_COMPA_vect) {

}
