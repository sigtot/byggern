/**
 * @file Joy_state.h
 * @brief Joystick state operations
 */
#ifndef JOY_STATE_H
#define JOY_STATE_H

/**
 * @brief joystick directions
 */
typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL,
} Dir;

/**
 * @brief joystick state
 */
typedef struct Joy_state {
    int x;  // -100 -> 100
    int y;  // -100 > 100
    Dir dir;
} Joy_state;

/**
 * @brief joystick Get joystick states
 * @param joy_state Struct containing the joystick state
 * @return x position of the joystick state scaled for use as servo value
 */
int Joy_state_get_servo_value(Joy_state joy_state);

#endif
