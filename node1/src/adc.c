#ifndef F_CPU
#define F_CPU 4915200
#endif
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#include "multifunction.h"

void adc_test() {
    joy_print_state();
    // slider_print_state();
    buttons_print_state();

    _delay_ms(100);
}
