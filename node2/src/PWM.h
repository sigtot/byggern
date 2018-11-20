/**
 * @file PWM.h
 * @brief PWM signal generation for servo
 */

#ifndef PWM_H
#define PWM_H

/**
 * Initialization of the PWM (fast mode) using timer/counter from atmega2560
 */
void PWM_init();

/**
 * PWM signal duty cycle generation
 * @param duty Desired duty cycle for the PWM signal
 */
void PWM_set_duty_cycle(double duty);

#endif
