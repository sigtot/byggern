#include "parameters.h"
#include "control.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "reference_state.h"

#define FREQ 400

#define MAX_INT_VAL 65536

#define SUM_SCALER 1
#define DOWNSCALER 100

#define abs(x) ((x)<0 ? -(x) : (x))

static volatile uint16_t counter;
static double time_step = (1 / (double) FREQ);

static int16_t error_sum = 0;
static int16_t K_p = MOTOR_DEFAULT_KP;
static int16_t K_i = MOTOR_DEFAULT_KI;

void control_init_timer() {
    TCNT3 = 0; // Reset timer high register
    OCR3A = 0x2400; // About 808Hz
    // Enable CTC mode
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);

    TCCR3B |= (1 << CS31) | (1 << WGM32);
    TIMSK3 |= (1 << OCIE3A); // Enable interrupts for TIMER3A
}

void control_init() {
    control_init_timer();
}

// Returns values between -MOTOR_MIN_VAL and MOTOR_MIN_VAL
int16_t get_control_input(int16_t reference, int16_t position, int16_t prev_position) {
    int16_t err = reference - position;

    int16_t control_input = K_p * err + K_i * error_sum;

    control_input /= DOWNSCALER;

    error_sum += err / DOWNSCALER;

    // Don't actuate motor in the treshhold -MOTOR_ZERO_TRESH -> +MOTOR_ZERO_TRESH
    if (abs(control_input) < MOTOR_ZERO_TRESH) {
        return 0;
    }

    // Compensate for motor's deadband of -MOTOR_MIN_VAL -> +MOTOR_MIN_VAL
    int shift = 0;
    if (abs(control_input) < MOTOR_MIN_VAL) {
        shift = (control_input < 0) ? -MOTOR_MIN_VAL : MOTOR_MIN_VAL;
    }
    return control_input + shift;
}

ISR(TIMER3_COMPA_vect)
{
    counter++;
    if (!(counter % 2)) {
        int16_t prev_position = Get_motor_pos();
        int16_t motor_val = MOTOR_Read_Encoder();
        Set_motor_pos(prev_position + motor_val);
        MOTOR_Actuate(get_control_input(Get_motor_reference(), Get_motor_pos(), prev_position));
        if (!(counter % 50)) {
            printf("input=%d, sumerror=%d\n\r", get_control_input(Get_motor_reference(), Get_motor_pos(), prev_position), error_sum);
        }
    }
}
