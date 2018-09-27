#ifndef F_CPU
#define F_CPU 4915200
#endif
#include <stdint.h>
#include "P_driver.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>

#define ADC 0x1400
#define PI 3.14159265
#define NEUTRAL_TRESH 20

int to_percent(uint8_t i) {
  return (int) i * ((float)200)/((float)256) - 100;
}

void joy_print_state() {
  Joy_state state = joy_get_state();
  printf("(%2d%c, %02d%c)\n\r", state.x, '%', state.y, '%');
}

Joy_state joy_get_state() {
  MCUCR |= (1 << SRE); // Enable external memory interface
  volatile char *memory = (char *) 0x0000;
  memory[ADC] = (1 << 2); // CH1
  _delay_ms(1); // Delay to wait for
  uint8_t x = memory[ADC];
  memory[ADC] = 1 | (1 << 2); // CH2
  _delay_ms(1); // Delay to wait for
  uint8_t y = memory[ADC];

  int x_percent = to_percent(x);
  int y_percent = to_percent(y);

  double ang = atan2(((double) y_percent)/((double) x_percent)));
  Dir dir;
  if(ang < - PI / 2 || ang > PI / 2) {
    dir = LEFT;
  }
  if(ang < PI / 4 && ang > - PI / 4) {
    dir = RIGHT;
  }
  if(ang < 3 * PI / 4 && ang > PI / 4) {
    dir = UP:
  }
  if(ang < - PI / 4 && ang > - 3 * PI / 4) {
    dir = DOWN;
  }
  if(sqrt(x_percent * x_percent + y_percent * y_percent) <= NEUTRAL_TRESH) {
    dir = NEUTRAL;
  }

  Joy_state state = {x_percent, y_percent, dir};
  return state;
}
