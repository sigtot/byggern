#ifndef JOY_POS_SENDER_H
#define JOY_POS_SENDER_H

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL,
} Dir;

typedef struct Joy_state {
    int x; // -100 -> 100
    int y; // -100 > 100
    Dir dir;
} Joy_state;

void joy_pos_send(Joy_state joy_state);

#endif
