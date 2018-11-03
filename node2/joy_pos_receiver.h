#ifndef JOY_POS_RECEIVER_H
#define JOY_POS_RECEIVER_H

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL,
} Dir;

typedef struct Joy_state {
    int x; // -100 -> 100
    int y; // -100 > 100
    Dir dir;
} Joy_state;

void joy_pos_receive();

#endif
