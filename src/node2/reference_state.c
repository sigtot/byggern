#include "reference_state.h"
#include "parameters.h"

Reference_State reference_state = {0, 0, 100}; // TODO: Make static

int Get_servo_reference() {
    return reference_state.servo_reference;
}

void Set_servo_reference(int val) {
    reference_state.servo_reference = val;
}

int Get_motor_reference() {
    return reference_state.motor_reference;
}

void Set_motor_reference(int val) {
    reference_state.motor_reference = val;
}

void Set_ir_value(int ir_value) {
    reference_state.ir_value = ir_value;
}

int Ir_is_blocked() {
    return reference_state.ir_value <= IR_BLOCK_THRESH;
}
