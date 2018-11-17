#include "ir.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include "../../common/src/filter.h"
#include "../../common/lib/Queue.h"
#include "reference_state.h"
#include "parameters.h"
#include "adc.h"

static struct Queue* measurements;

ISR(ADC_vect) {
    dequeue(measurements);  // Discard oldest measurement
    enqueue(measurements, adc_read_value());
    Set_ir_value(get_average(measurements));
}

void ir_init() {
    measurements = createQueue(IR_FILTER_QUALITY);
    adc_init();
}
