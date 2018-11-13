#ifndef STATE_H
#define STATE_H

typedef struct state {
    int servo_pos;
    int motor_pos;
    int motor_reference;
    int ir_value;
} State;

int Get_servo_pos(void);

void Set_servo_pos(int servo_pos);

int Get_motor_pos(void);

void Set_motor_pos(int motor_pos);

int Get_motor_reference(void);

void Set_motor_reference(int motor_pos);

void Set_ir_value(int ir_value);

int Ir_is_blocked();

#endif
