#include "parameters.h"
#include "control.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "reference_state.h"

#define FREQ 400

#define MAX_INT_VAL 65536

#define ENCODER_SCALE 10
#define SUM_SCALER 1
#define DOWNSCALER 100

// Motorbox pins
#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5 // Active low
#define RST PH6 // Active low

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
    // Set K port (MJ2) as input
    DDRK = 0x0;

    // Set pins in H port (MJ1) as output
    DDRH |= (1 << RST)| // reset pin
            (1 << OE) | // output enable pin
            (1 << EN) | // enable pin
            (1 << SEL)| // select high or low register pin
            (1 << DIR); // motor direction pin

    // Set counter to 0
    PORTH &= ~(1 << RST);
    printf("PORTH after: %02x", PORTH);

    // Enable motor
    PORTH |= (1 << EN);

    // Enable encoder output
    PORTH &= ~(1 << OE);

    calibrate_motor();
    control_init_timer();
}

void control_set_motor_direction(MotorDir dir) {
    switch (dir) {
    case LEFT:
        PORTH &= ~(1 << DIR);
        break;
    case RIGHT:
        PORTH |= (1 << DIR);
    }
    _delay_us(100);
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
    double mul = 1;
    if (abs(control_input) < MOTOR_MIN_VAL) {
        mul = (double)MOTOR_MIN_VAL / (double)control_input;
    }
    return abs(mul) * control_input;
}

void calibrate_motor() {
    control_set_motor_direction(LEFT);
    MOTOR_Send_Voltage(120);
    _delay_ms(500);
    control_set_motor_direction(RIGHT);
    MOTOR_Send_Voltage(120);
    _delay_ms(200);
    MOTOR_Send_Voltage(0);
    _delay_ms(500);
}

void actuate_motor(int16_t input) {
    if (input < 0) {
        control_set_motor_direction(LEFT);
        MOTOR_Send_Voltage(input);
    } else {
        control_set_motor_direction(RIGHT);
        MOTOR_Send_Voltage(input);
    }
}

int16_t read_encoder_value() {
    volatile int16_t value = 0;
    // Enable output
    PORTH &= ~(1 << OE);

    // Select MSB
    PORTH &= ~(1 << SEL);

    _delay_us(250);

    // Read MSB
    value |= (PINK << 8);

    // Select LSB
    PORTH |= (1 << SEL);

    _delay_us(250);

    // Read LSB
    value |= PINK;

    // Toggle reset
    if (PORTH & (1 << RST)) {
        PORTH &= ~(1 << RST);
    } else {
        PORTH |= (1 << RST);
    }

    // Disable output
    PORTH |= (1 << OE);

    return (-1) * value / ENCODER_SCALE; // Return negative since direction is flipped
}

ISR(TIMER3_COMPA_vect)
{
    counter++;
    if (!(counter % 2)) {
        int16_t prev_position = Get_motor_pos();
        int16_t motor_val = read_encoder_value();
        Set_motor_pos(prev_position + motor_val);
        actuate_motor(get_control_input(Get_motor_reference(), Get_motor_pos(), prev_position));
        if (!(counter % 200)) {
            printf("input=%d, sumerror=%d\n\r", get_control_input(Get_motor_reference(), Get_motor_pos(), prev_position), error_sum);
        }
    }
}
