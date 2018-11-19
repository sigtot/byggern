#ifndef CONTROL_H
#define CONTROL_H
#include <stdint.h>

int16_t control_get_input(int16_t reference, int16_t position);
void controller_calculate_and_actuate();

void control_set_kp(double val);

void control_set_ki(double val);

void control_set_kd(double val);

double control_get_kp();

double control_get_ki();

double control_get_kd();

#endif
