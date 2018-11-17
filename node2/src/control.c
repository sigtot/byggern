#include "parameters.h"
#include "control.h"
#include "reference_state.h"
#include "motor.h"

#define DOWNSCALER 100

#define abs(x) ((x) < 0 ? -(x) : (x))

static int16_t error_sum = 0;
static int16_t K_p = MOTOR_DEFAULT_KP;
static int16_t K_i = MOTOR_DEFAULT_KI;

int counter = 0;
// Returns values between -MOTOR_MIN_VAL and MOTOR_MIN_VAL
int16_t control_get_input(int16_t reference,
                          int16_t position) {



    int16_t err = reference - position;

    int16_t control_input = K_p * err + K_i * error_sum;

    control_input /= DOWNSCALER;


    error_sum += err / DOWNSCALER;

    // Don't actuate motor in the threshold -MOTOR_ZERO_TRESH ->
    // +MOTOR_ZERO_TRESH
    if (abs(control_input) < MOTOR_ZERO_TRESH) {
        return 0;
    }


    // Compensate for motor's deadband of -MOTOR_MIN_VAL -> +MOTOR_MIN_VAL
    double mul = 1;
    if (abs(control_input) < MOTOR_MIN_VAL) {
        mul = (double)MOTOR_MIN_VAL / (double)control_input;
    }
    return (int16_t)(abs(mul) * control_input);
}

void controller_calculate_and_actuate() {
    int16_t prev_position = Get_motor_pos();
    int16_t motor_val = motor_read_encoder();
    Set_motor_pos(prev_position + motor_val);
    motor_actuate(control_get_input(Get_motor_reference(), prev_position + motor_val));
}
