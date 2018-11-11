#include "control.h"
#include <avr/interrupt.h>
#include <avr/io.h>

ISR(TIMER3_COMPA_vect)
{
    printf("Hello world\n");
}
