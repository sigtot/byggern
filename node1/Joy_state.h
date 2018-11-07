#ifndef JOY_STATE_H
#define JOY_STATE_H

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL,
} Dir;

typedef struct Joy_state {
    int x; // -100 -> 100
    int y; // -100 > 100
    Dir dir;
} Joy_state;

#endif
