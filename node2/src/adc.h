/**
 * @file adc.h
 * @brief implements analog to digital conversion
 */

#ifndef ADC_H
#define ADC_H

/**
 * Read digital value in ADCl/H registers 
 * from the analog-to-digital conversion
 */
int adc_read_value();

/**
 * Initialize the analog to digital conversion with 128 prescaler
 */
void adc_init();

#endif
