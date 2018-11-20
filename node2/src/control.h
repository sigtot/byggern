/**
 * @file control.h
 * @brief Implements a PI controller
 */

#ifndef CONTROL_H
#define CONTROL_H
#include <stdint.h>

/**
 * Function calculates the controllers input based on reference and position
 * Note: guards for being within the threshold
 * and deadband compensations are included
 * @param reference The reference or desired value
 * @param position The actual position value
 * @return control input as a 16-bit integer
 */
int16_t control_get_input(int16_t reference, int16_t position);

/**
 * Set motor position and actuate motor
 */
void controller_calculate_and_actuate();

/**
 * Set K_p gain
 * @param val Value of the K_p gain
 */
void control_set_kp(double val);

/**
 * Set K_i gain
 * @param val Value of the K_i gain
 */
void control_set_ki(double val);

/**
 * Set K_d gain
 * @param val Value of the K_d gain
 */
void control_set_kd(double val);

/**
 * Get K_p gain
 * @return K_p gain
 */
double control_get_kp();

/**
 * Get K_i gain
 * @return K_i gain
 */
double control_get_ki();

/**
 * Get K_d gain
 * @return K_d gain
 */
double control_get_kd();

#endif
