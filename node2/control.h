#ifndef CONTROL_H
#define CONTROL_H
#include <avr/interrupt.h>
#include <avr/io.h>

typedef enum MotorDir {LEFT, RIGHT} MotorDir;
void control_init_timer();
void control_init();

#endif
