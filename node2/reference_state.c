#include "reference_state.h"

Reference_State reference_state = {0, 0};

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
