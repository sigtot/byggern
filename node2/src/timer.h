/**
 * @file timer.h
 * @brief Timer module for timer based interrupts
 */
#ifnd

#ifndef TIMER_H
#define TIMER_H

/**
 * Initialization of timer (CTC mode)
 */
void timer_init();

/**
 * Flags for the interrupt routine
 */
int _timer_flag_SHOULD_CALC_INPUT;
int _timer_flag_SHOULD_CALC_SERVO;
#endif
