#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x800 ? '1' : '0'), \
  (byte & 0x400 ? '1' : '0'), \
  (byte & 0x200 ? '1' : '0'), \
  (byte & 0x100 ? '1' : '0'), \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#ifndef F_CPU
#define F_CPU 4915200
#endif
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#define ADC 0x1400

#define JOY_Y 4
#define JOY_X 5
#define SLIDER_R 6
#define SLIDER_L 7
#define TIMESCALE 1

void chip_select() {
  PORTC |= (1 << PC2);
  PORTC &= ~(1 << PC3);
}

/**
 * Deselects the adc (and selects the OLED as a side effect)
 */
void chip_deselect() {
  PORTC &= ~(1 << PC2);
  PORTC &= ~(1 << PC3);
}

void adc_test() {
  volatile char *memory = (char *) 0x0000;

  memory[ADC] = (1 << 2); // CH1
  _delay_ms(1); // Delay to wait for
  uint8_t x = memory[ADC];

  memory[ADC] = 1 | (1 << 2); // CH2
  _delay_ms(1); // Delay to wait for
  uint8_t y = memory[ADC];
  printf("(%d,%d)\n\r", x, y);
}

/*
void adc_test() {

    //printf("adc test: \n\r");
    DDRD |= (1 << PD6);
    DDRD |= (1 << PA7);
    DDRA |= (1 << PA2);
    DDRB &= ~(1 << PB0);
    DDRC |= (1 << PC2);
    DDRC |= (1 << PC3);

    chip_select(); // Set CS LOW
    _delay_ms(200);
    PORTD &= ~(1 << PD6); // Set WR LOW
    _delay_ms(200);
    PORTD |= (1 << PD7); // Set RD HIGH
    _delay_ms(200);
    while (!(PINB & (1 << PB0))); // Wait for INTR to go HIGH
    _delay_ms(200);
    PORTA |= (1 << PA2); // Write mux address
    _delay_ms(200);
    PORTD |= (1 << PD6); // Set WR HIGH
    _delay_ms(200);
    DDRA &= 0; // Set port A to read mode
    _delay_ms(200);
    //printf("Got this far\n\r");
    chip_deselect(); // Set CS HIGH
    _delay_ms(200);
    //printf(BYTE_TO_BINARY_PATTERN"\n\r", BYTE_TO_BINARY(PINB));
    while (PINB & (1 << PB0)); // Wait for INTR to go LOW
    _delay_ms(200);
    //printf("7");
    chip_select(); // Set CS LOW
    _delay_ms(200);
    //printf("8");
    _delay_ms(200);
    PORTD &= ~(1 << PD7); // Set RD LOW
    _delay_ms(200);
    //printf("9");
    uint8_t data = PINA; // Get data
    _delay_ms(200);
    //printf("10");
    PORTD |= (1 << PD7); // Set RD HIGH
    _delay_ms(200);
    //printf("11");
    _delay_ms(200);
    printf("Read from adc: "BYTE_TO_BINARY_PATTERN"\n\r", BYTE_TO_BINARY(data));
    //printf("adc test finished\n\r");
    chip_deselect();
    _delay_ms(200);
}
*/

//interrupt handler
//IRQ0 Handler: EXT_INT0

/*
void adc_test() {
    volatile char *adc = (char *) 0x1400; // Start address for the SRAM

    for (uint16_t i = 0x1400; i < 0x14FF; i++) {
      uint8_t some_value = rand();
      ext_ram[i] = some_value;
      uint8_t retreived_value = ext_ram[i];

    uint8_t joy_y = adc[JOY_Y];
    printf("Read from adc: "BYTE_TO_BINARY_PATTERN" at "BYTE_TO_BINARY_PATTERN"\n\r",
      BYTE_TO_BINARY(joy_y),
      BYTE_TO_BINARY(0x1400  + JOY_Y));
}
*/
