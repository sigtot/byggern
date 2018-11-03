#include <avr/io.h>
#include "PWM.h"


//TOP = 311
//Prescaler = 1024


#define F_CPU 16000000ul


void PWM_init() {

    /*PWM signal skal kunne dyttes ut av OC2A(PB4)
    */

    DDRB |= 0xFF;
    //Set fast MODE
    TCCR1A |= (1 << WGM21) | (1 << WGM20);
    //Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
    //Set TOP
    ICR1H = 0;
    ICR1L = 0xFF;
    OCR1AL = 67;
    OCR1AH = 256;


}


//COM1A =
