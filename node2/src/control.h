#ifndef CONTROL_H
#define CONTROL_H
#include <stdint.h>

int16_t control_get_input(int16_t reference,
                          int16_t position,
                          int16_t prev_position);
void controller_calculate_and_actuate();

#endif
