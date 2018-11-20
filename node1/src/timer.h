/**
 * @file timer.h
 * @brief Timer module for timer based interrupts
 */

#ifndef TIMER_H
#define TIMER_H

/**
 * Initialization of timer (CTC mode), prescale 1
 * note: interrupt driven
 */
void timer_init();

/**
 * Flag for the interrupt routine
 */
int _timer_flag_SHOULD_CALC_INPUT;

#endif
