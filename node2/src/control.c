#include "parameters.h"
#include "control.h"
#include "reference_state.h"
#include "motor.h"
#include <stdint.h>

#define DOWNSCALER 100

#define abs(x) ((x) < 0 ? -(x) : (x))

static int16_t error_sum = 0;
static double K_p = MOTOR_DEFAULT_KP;
static double K_i = MOTOR_DEFAULT_KI;
static double K_d = 0;

int counter = 0;
// Returns values between -MOTOR_MIN_VAL and MOTOR_MIN_VAL
int16_t control_get_input(int16_t reference, int16_t position) {
    static int16_t inp = 0;
    double err = (double)(reference - position);
    int16_t control_input = (int16_t)(K_p * err + K_i * error_sum);
    error_sum += err;

    // Don't actuate motor in the threshold -MOTOR_ZERO_TRESH ->
    // +MOTOR_ZERO_TRESH
    if (abs(control_input) < MOTOR_ZERO_TRESH) {
        return 0;
    }

    // Compensate for motor's deadband of -MOTOR_MIN_VAL -> +MOTOR_MIN_VAL
    if (abs(control_input) < MOTOR_MIN_VAL) {
        return (control_input < 0 ? (-1) : 1) * MOTOR_MIN_VAL;
    }

    if (abs(control_input) > MOTOR_MAX_VAL) {
        return (control_input < 0 ? (-1) : 1) * MOTOR_MAX_VAL;
    }
    return control_input;
}

void controller_calculate_and_actuate() {
    int16_t prev_position = Get_motor_pos();
    int16_t motor_val = motor_read_encoder();
    int16_t motor_pos = prev_position + motor_val;
    Set_motor_pos(motor_pos);
    motor_actuate(control_get_input(Get_motor_reference(), motor_pos));
}

void control_set_kp(double val) {
    K_p = val;
}

void control_set_ki(double val) {
    K_i = val;
}

void control_set_kd(double val) {
    K_d = val;
}

double control_get_kp() {
    return K_p;
}

double control_get_ki() {
    return K_i;
}

double control_get_kd() {
    return K_d;
}
