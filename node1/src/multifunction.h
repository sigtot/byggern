#ifndef MULTIFUNCTION_H
#define MULTIFUNCTION_H

#include "Joy_state.h"

typedef struct Sliders {
    int left;
    int right;
} Slider;

typedef struct Buttons {
    int right;
    int left;
    int joy;
} Button;

void set_channels(int chan1);

void joy_print_state();
Joy_state joy_get_state();
int joy_get_dir(int x, int y);

void slider_print_state();
Slider slider_get_state();

void buttons_print_state();
Button buttons_get_state();

#endif
