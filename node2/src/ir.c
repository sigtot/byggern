#include "ir.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include "../../common/src/filter.h"
#include "../../common/lib/Queue.h"
#include "reference_state.h"
#include "parameters.h"

#define ADC0 PF0
static struct Queue* measurements;

ISR(ADC_vect) {
    // Read the lower register
    int ir_val = ADCL;

    /* ADCH register needs to be read after ADCL for next conversion to be written
     * However, this value is not needed, as the maximum expected IR value is
     * quite low */
    int discard = ADCH;

    Set_ir_value(get_average(measurements));
    discard = dequeue(measurements); // Discard oldest measurement
    enqueue(measurements, ir_val);

    // Start next conversion
    ADCSRA |= 1 << ADSC;
}

// Rename to ADC_init (and move?)
void ir_init() {
    measurements = createQueue(IR_FILTER_QUALITY);
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
