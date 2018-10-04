#ifndef F_CPU
#define F_CPU 4915200
#endif
#include <stdint.h>
#include "P_driver.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>

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

#define ADC 0x1400
#define PI 3.14159265
#define NEUTRAL_TRESH 20

void set_channels(int chan) {
    MCUCR |= (1 << SRE); // Enable external memory interface
    volatile char *memory = (char *) 0x0000;
    switch(chan) {
        case 1 :
            memory[ADC] = 4;//(1 << 2); // CH1
            break;
        case 2 :
            memory[ADC] = 5;//1 | (1 << 2); // CH2
            break;
        case 3 :
            memory[ADC] =  6;//(1 << 1) | (1 << 2);
            break;
        case 4 :
            memory[ADC] = 7;//1 | (1 << 1) | (1 << 2);
    }
    _delay_ms(1);
}

int to_percent(uint8_t i) {
    return (int) i * ((float)200)/((float)256) - 100;
}

void joy_print_state() {
    Joy_state state = joy_get_state();
    printf("(%2d%c, %02d%c, %d)\n\r", state.x, '%', state.y, '%', state.dir);
}

Joy_state joy_get_state() {
    volatile char *memory = (char *) 0x0000;
    set_channels(1);
    uint8_t x = memory[ADC];
    set_channels(2);
    uint8_t y = memory[ADC];

    int x_percent = to_percent(x);
    int y_percent = to_percent(y);

    int dir = joy_get_dir(x_percent, y_percent);

    Joy_state state = {x_percent, y_percent, dir};
    return state;
}

int joy_get_dir(int x, int y) {
    double ang = atan2(((double) y),((double) x));
    Dir dir;
    if(ang < - PI / 2 || ang > PI / 2) {
        dir = LEFT;
  }
  if(ang < PI / 4 && ang > - PI / 4) {
      dir = RIGHT;
  }
  if(ang < 3 * PI / 4 && ang > PI / 4) {
      dir = UP;
  }
  if(ang < - PI / 4 && ang > - 3 * PI / 4) {
      dir = DOWN;
  }
  if(sqrt(x * x + y * y) <= NEUTRAL_TRESH) {
      dir = NEUTRAL;
  }
  return dir;
}

void joy_calibrate() {

}

void slider_print_state() {
    Slider slider = slider_get_state();
    printf("Left slider: %d    Right slider: %d\n\r", slider.left, slider.right);
}

Slider slider_get_state() {
    volatile char *memory = (char *) 0x0000;
    set_channels(3);
    uint8_t right = memory[ADC];
    set_channels(4);
    uint8_t left = memory[ADC];
    Slider slider = {left, right};
    return slider;
}

void buttons_print_state() {
    Button button = buttons_get_state();
    //printf("left button: %d     right button: %d\n\r", button.left, button.right);
}

Button buttons_get_state() {
    MCUCR &= ~(1 << SRE); // disable external memory interface
    DDRB &= ~(1 << PB1);
    DDRB &= ~(1 << PB2);

    int left = PINB & (1 << PB1);
    int right = PINB & (1 << PB2);
    if (left){
        printf(" left true\n\r");
    }
    if (right){
        printf(" right true\n\r");
    }

    Button button = {right, left};
    //printf("left button: %d     right button: %d\n\r", left, right);

    return button;
}
