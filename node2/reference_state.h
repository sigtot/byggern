#ifndef REFERENCE_STATE_H
#define REFERENCE_STATE_H

typedef struct Reference_State {
    int servo_pos;
    int motor_pos;
    int ir_value;
} Reference_State;

int Get_reference_servo_pos(void);

void Set_reference_servo_pos(int servo_pos);

int Get_reference_motor_pos(void);

void Set_reference_motor_pos(int servo_pos);

void Set_ir_value(int ir_value);

int Ir_is_blocked();

#endif
