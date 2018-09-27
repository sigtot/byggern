#ifndef P_DRIVER_H
#define P_DRIVER_H

typedef enum Dir{LEFT, RIGHT, UP, DOWN, NEUTRAL};

typedef struct Joy_state {
  int x; // -100 -> 100
  int y; // -100 > 100
  Dir dir;
} Joy_state;

void joy_print_state();
Joy_state joy_get_state();

#endif
