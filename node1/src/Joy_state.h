#ifndef JOY_STATE_H
#define JOY_STATE_H

typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL,
} Dir;

typedef struct Joy_state {
    int x;  // -100 -> 100
    int y;  // -100 > 100
    Dir dir;
} Joy_state;

int Joy_state_get_servo_value(Joy_state joy_state);

#endif
