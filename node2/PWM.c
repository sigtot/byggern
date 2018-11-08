#include <avr/io.h>
#include "PWM.h"
#include "parameters.h"
#include <stdint.h>

// Canculated values
// TOP = 311
// Prescaler = 1024


#define DDR_OC1A DDRB
#define OC1A DDB5

#define PRESCALER 1024 // Warning: Prescaler is configured by bits CS10-CS12
#define TOP ((uint16_t)( (double)F_CPU/((double)PWM_FREQ * PRESCALER)) - 1)

void PWM_Normal_Init() {

}

void PWM_init() {

    /*PWM signal skal kunne dyttes ut av OC2A(PB4)
    */

    // Set data direction OUT on OC1A (PB5)
    DDR_OC1A |= (1 << OC1A);

    // Set fast PWM mode
    TCCR1A &= ~(1 << WGM10); // TODO: Remove
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << WGM13);

    // Override normal port operation on OC1A
    TCCR1A &= ~(1 << COM1A0); // TODO: Remove
    TCCR1A |= (1 << COM1A1);

    // Select clock source with prescaler 1024
    TCCR1B |= (1 << CS12)|(1 << CS10);

    // Set TOP values
    //ICR1H = ((TOP & 0xFF00) >> 2);
    ICR1H = 0x01;
    ICR1L = 0x37; // (TOP & 0xFF);
    printf("Top:  %04x\n\r", TOP);
    printf("Toph: %04x\n\r", ((TOP & 0xFF00) >> 2)); // This outputs 0x40, but should be 0x01, why?
    printf("Topl: %04x\n\r", (TOP & 0xFF));
}

void PWM_set_duty_cycle(double duty) {
    uint16_t BOTTOM = (uint16_t) (duty * PWM_FREQ * (TOP + 1));
    OCR1AH = 0x00;
    OCR1AL = (BOTTOM & 0xFF);
    printf("Bottom: %04x\n\r", BOTTOM);
}

//COM1A =
