#include "timer.h"
#include "control.h"
#include "motor.h"
#include "reference_state.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#define FREQ 400
static volatile uint16_t counter = 0;
static double time_step = (1 / (double) FREQ);

void timer_init() {
    printf("Timer initiated\n\r");
    TCNT3 = 0; // Reset timer high register
    OCR3A = 0x2400; // About 808Hz
    // Enable CTC mode
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);

    TCCR3B |= (1 << CS31) | (1 << WGM32);
    TIMSK3 |= (1 << OCIE3A); // Enable interrupts for TIMER3A}
}

ISR(TIMER3_COMPA_vect) {
    counter++;
    if (!(counter % 2)) {
        int16_t prev_position = Get_motor_pos();
        int16_t motor_val = motor_read_encoder();
        Set_motor_pos(prev_position + motor_val);
        motor_actuate(control_get_input(Get_motor_reference(), Get_motor_pos(), prev_position));
    }
}
