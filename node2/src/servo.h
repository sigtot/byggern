/**
 * @file servo.h
 * @brief Controls the servo position.
 */
#ifndef SERVO_H
#define SERVO_H

/**
 * @brief Initialize servo.
 * Note: Interrupts must be enabled globally for the PWM generation to work
 */
void servo_init();

/**
 * @brief Set servo position.
 * Servo needs to be initialized.
 * @param servo_pos servo position ranging from 0 to 100
 */
void servo_set_pos(int servo_pos);

#endif
