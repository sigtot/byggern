#include "gal_test.h"
#include <util/delay.h>
#include <avr/io.h>
#include "driver.h"
#define A10 PC2
#define A11 PC3
#define TIMESCALE 10000

void GAL_test() {
  printf("======== Gal Test ========\n\r");

  printf("Testing ram_cs: (expecting HIGH on P19)...\n\r");
  PORTC |= (1 << A11);
  PORTC |= (1 << A10);
  _delay_ms(TIMESCALE);
  PORTC &= ~(1 << A10);
  _delay_ms(TIMESCALE);

  printf("Testing adc_cs: (expecting LOW on P18)...\n\r");
  PORTC &= ~(1 << A11);
  PORTC |= (1 << A10);
  _delay_ms(2 * TIMESCALE);

  printf("Testing oled_cs: (expecting LOW on P17)...\n\r");
  PORTC &= ~(1 << A11);
  PORTC &= ~(1 << A10);
  _delay_ms(2 * TIMESCALE);

  printf("===== Test Completed =====\n\r");
}
