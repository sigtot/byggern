#include "timer.h"
#include "control.h"
#include "motor.h"
#include "reference_state.h"
#include <avr/interrupt.h>
#include <avr/io.h>

static volatile uint16_t counter = 0;
int _timer_flag_SHOULD_CALC_INPUT = 0;
int _timer_flag_SHOULD_CALC_SERVO = 0;

void timer_init() {
    TCNT3 = 0;       // Reset timer high register
    OCR3A = 0x2400;  // About 408Hz
    // Enable CTC mode
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);

    TCCR3B |= (1 << CS31) | (1 << WGM32);
    TIMSK3 |= (1 << OCIE3A);  // Enable interrupts for TIMER3A
}

ISR(TIMER3_COMPA_vect) {
    counter++;
    _timer_flag_SHOULD_CALC_INPUT = 1;
    if (!(counter%50000)) {
        _timer_flag_SHOULD_CALC_SERVO = 1;
    }
}
