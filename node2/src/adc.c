#include "adc.h"
#include <avr/io.h>

#define ADC0 PF0

int adc_read_value() {
    // Read the lower register
    int reading = ADCL;

    /* ADCH register needs to be read after ADCL for next conversion to be written
     * However, this value is not needed, as the maximum expected IR value is
     * quite low */
    int discard = ADCH;

    // Start next conversion
    ADCSRA |= 1 << ADSC;

    return reading;
}

void adc_init() {
    // Define ADC0 (PF0) as analog input pin
    DDRA |= (1 << ADC0);

    // Enable ADC with interrupts
    ADCSRA |= (1 << ADEN)|(1 << ADIE);

    // Set ADC prescaler with division factor 128
    ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);

    // Set AVCC as reference
    ADMUX |= (1 << REFS0);

    // Start first conversion
    ADCSRA |= (1 << ADSC);
}
