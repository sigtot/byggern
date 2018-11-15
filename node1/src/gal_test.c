#include "gal_test.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#define TIMESCALE 10000

void GAL_test() {
  printf("======== Gal Test ========\n\r");
  DDRC |= (1 << PC2) | (1 << PC3);

  printf("Testing ram_cs: (expecting HIGH on P19)...\n\r");
  PORTC |= (1 << PC3);
  PORTC |= (1 << PC2);
  _delay_ms(TIMESCALE);
  PORTC &= ~(1 << PC2);
  _delay_ms(TIMESCALE);

  printf("Testing adc_cs: (expecting LOW on P18)...\n\r");
  PORTC &= ~(1 << PC3);
  PORTC |= (1 << PC2);
  _delay_ms(2 * TIMESCALE);

  printf("Testing oled_cs: (expecting LOW on P17)...\n\r");
  PORTC &= ~(1 << PC3);
  PORTC &= ~(1 << PC2);
  _delay_ms(2 * TIMESCALE);

  printf("===== Test Completed =====\n\r");
}
