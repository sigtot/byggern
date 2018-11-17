#include "timer.h"
#include "control.h"
#include "motor.h"
#include "reference_state.h"
#include <avr/interrupt.h>
#include <avr/io.h>

static volatile uint16_t counter = 0;
static int should_calculate_input_flag = 0;

void timer_init() {
    printf("Timer initiated\n\r");
    TCNT3 = 0;       // Reset timer high register
    OCR3A = 0x28A0;  // About 408Hz
    // Enable CTC mode
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);

    TCCR3B |= (1 << CS31) | (1 << WGM32);
    TIMSK3 |= (1 << OCIE3A);  // Enable interrupts for TIMER3A
}

inline int timer_flag_should_calculate_input() {
    return should_calculate_input_flag;
}

void timer_flag_finished_calculating_input() {
    should_calculate_input_flag = 0;
}

ISR(TIMER3_COMPA_vect) {
    counter++;
    if (!(counter % 2)) {
        should_calculate_input_flag = 1;
    }
}
