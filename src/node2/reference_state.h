#ifndef REFERENCE_STATE_H
#define REFERENCE_STATE_H

typedef struct Reference_State {
    int servo_reference;
    int motor_reference;
    int ir_value;
} Reference_State;

int Get_servo_reference(void);

void Set_servo_reference(int servo_pos);

int Get_motor_reference(void);

void Set_motor_reference(int servo_pos);

void Set_ir_value(int ir_value);

int Ir_is_blocked();

#endif
