#include "parameters.h"
#include "control.h"


#define DOWNSCALER 100

#define abs(x) ((x)<0 ? -(x) : (x))

static int16_t error_sum = 0;
static int16_t K_p = MOTOR_DEFAULT_KP;
static int16_t K_i = MOTOR_DEFAULT_KI;

// Returns values between -MOTOR_MIN_VAL and MOTOR_MIN_VAL
int16_t control_get_input(int16_t reference, int16_t position, int16_t prev_position) {
    int16_t err = reference - position;

    int16_t control_input = K_p * err + K_i * error_sum;

    control_input /= DOWNSCALER;

    error_sum += err / DOWNSCALER;

    // Don't actuate motor in the treshhold -MOTOR_ZERO_TRESH -> +MOTOR_ZERO_TRESH
    if (abs(control_input) < MOTOR_ZERO_TRESH) {
        return 0;
    }

    // Compensate for motor's deadband of -MOTOR_MIN_VAL -> +MOTOR_MIN_VAL
    double mul = 1;
    if (abs(control_input) < MOTOR_MIN_VAL) {
        mul = (double)MOTOR_MIN_VAL / (double)control_input;
    }
    return abs(mul) * control_input;
}
