#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

typedef enum MotorDir { LEFT, RIGHT } MotorDir;

void MOTOR_Send_Voltage(unsigned char voltage);
void MOTOR_Init();
void motor_calibrate();
void motor_actuate(int16_t input);
int16_t motor_read_encoder();
void motor_set_direction(MotorDir dir);

#endif
