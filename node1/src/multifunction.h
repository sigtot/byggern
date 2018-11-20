
/**
 * @file multifunction.h
 * Get, set and print functions for the multifunctional board
 */
#ifndef MULTIFUNCTION_H
#define MULTIFUNCTION_H

#include "Joy_state.h"

/**
 * Struct containing the two sliders
 */
typedef struct Sliders {
    int left;
    int right;
} Slider;

/**
 * Struct containing the three buttons
 */
typedef struct Buttons {
    int right;
    int left;
    int joy;
} Button;

/**
 * ??
 */
void set_channels(int chan1);

/**
 * Print joystick state
 */
void joy_print_state();

/**
 * Get joystick states
 * @return Joystick state
 */
Joy_state joy_get_state();

/**
 * Get joystick direction
 * @param x X direction
 * @param y Y direction
 * @return joystick dir as a element in Dir enum
 */
int joy_get_dir(int x, int y);

/**
 * Print slider state
 */
void slider_print_state();

/**
 * Get slider states
 * @return slider state
 */
Slider slider_get_state();

/**
 * print button state
 */
void buttons_print_state();

/**
 * Get button state
 * @return button state
 */
Button buttons_get_state();

#endif
