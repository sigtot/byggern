/**
 * @file motor.h
 * @brief Handles the motor moving the cart in the ping pong game.
 */
#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

typedef enum MotorDir { LEFT, RIGHT } MotorDir;

/**
 * Send voltage to the motor.
 * @param voltage unsigned motor value proportional to the real life voltage input.
 */
void motor_send_voltage(unsigned char voltage);

/**
 * Initializes and calibrates the motor to a ready state.
 */
void motor_init();

/**
 * Sets the motor to its defined default position.
 */
void motor_calibrate();

/**
 * Actuates the motor with the given input.
 * @param input signed control input that corresponds to left (negative) og
 * right (positive) motion.
 */
void motor_actuate(int16_t input);

/**
 * Reads the accumulated encoder value from the motor.
 * @return encoder value as a signed integer.
 */
int16_t motor_read_encoder();

/**
 * Sets the direction of the motor.
 * @param dir left or right.
 */
void motor_set_direction(MotorDir dir);

#endif
