#include "reference_state.h"
#include "parameters.h"

Reference_State reference_state = {0, 0, 100}; // TODO: Make static

int Get_servo_pos() {
    return reference_state.servo_pos;
}

void Set_servo_pos(int servo_pos) {
    reference_state.servo_pos = servo_pos;
}

int Get_motor_pos() {
    return reference_state.motor_pos;
}

void Set_motor_pos(int motor_pos) {
    reference_state.motor_pos = motor_pos;
}

void Set_ir_value(int ir_value) {
    reference_state.ir_value = ir_value;
}

int Ir_is_blocked() {
    return reference_state.ir_value <= IR_BLOCK_THRESH;
}
