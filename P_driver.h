#ifndef P_DRIVER_H
#define P_DRIVER_H

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL,
} Dir;

typedef struct Joy_state {
  int x; // -100 -> 100
  int y; // -100 > 100
  Dir dir;
} Joy_state;

typedef struct Sliders {
  int left;
  int right;
} Slider;

void set_channels(int chan1);

void joy_print_state();
Joy_state joy_get_state();

int joy_get_dir(int x, int y);

void slider_print_state();
Slider slider_get_state();

#endif
