#include "reference_state.h"
#include "parameters.h"

Reference_State reference_state = {0, 0, 0, 100, 0};  // TODO: Make static

int Get_servo_reference() {
    return reference_state.servo_reference;
}

void Set_servo_reference(int val) {
    reference_state.servo_reference = val;
}

int16_t Get_motor_reference() {
    return reference_state.motor_reference;
}

void Set_motor_reference(int16_t val) {
    reference_state.motor_reference = val;
}

void Set_motor_pos(int16_t val) {
    reference_state.motor_pos = val;
}

int16_t Get_motor_pos() {
    return reference_state.motor_pos;
}

void Set_ir_value(int ir_value) {
    reference_state.ir_value = ir_value;
}

int Ir_is_blocked() {
    return reference_state.ir_value <= IR_BLOCK_THRESH;
}

int Get_solenoid_reference(void) {
    return reference_state.solenoid_reference;
}

void Set_solenoid_reference(int solenoid_reference) {
    reference_state.solenoid_reference = solenoid_reference;
}
