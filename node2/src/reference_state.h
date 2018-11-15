#ifndef REFERENCE_STATE_H
#define REFERENCE_STATE_H
#include <avr/io.h>

typedef struct Reference_State {
    int servo_reference;
    int motor_reference;
    int motor_pos;
    int ir_value;
    int solenoid_reference;
} Reference_State;

int Get_solenoid_reference(void);

void Set_solenoid_reference(int solenoid_reference);

int Get_servo_reference(void);

void Set_servo_reference(int servo_pos);

int16_t Get_motor_reference(void);

void Set_motor_reference(int16_t servo_pos);

int16_t Get_motor_pos();

void Set_motor_pos(int16_t val);

void Set_ir_value(int ir_value);

int Ir_is_blocked();

#endif
