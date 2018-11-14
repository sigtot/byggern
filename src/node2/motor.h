#ifndef MOTOR_H
#define MOTOR_H
#include <avr/io.h>

typedef enum MotorDir {LEFT, RIGHT} MotorDir;
void MOTOR_Init();
void MOTOR_Calibrate();
void MOTOR_Actuate();
int16_t MOTOR_Read_Encoder();

#endif
