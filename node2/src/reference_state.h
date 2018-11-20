/**
 * @file reference_state.h
 * Get and set functions for servo-, motor-, IR- and solenoid values
 */

#ifndef REFERENCE_STATE_H
#define REFERENCE_STATE_H
#include <avr/io.h>

/**
 * Struct containing all necessary states,
 * i.e. solenoid, servo, motor and IR states
 */
typedef struct Reference_State {
    int servo_reference;
    int motor_reference;
    int motor_pos;
    int ir_value;
    int solenoid_reference;
    int play_game_reference;
} Reference_State;

/**
 * @brief Get solenoid reference
 * @return solenoid reference as an integer
 */
int Get_solenoid_reference(void);

/**
 * @brief Set solenoid reference
 * @param val Desired reference for the solenoid
 */
void Set_solenoid_reference(int val);

/**
 * @Get servo reference
 * @return Servo reference as an integer
 */
int Get_servo_reference(void);

/**
 * @brief Set servo reference
 * @param val Desired reference for the servo position
 */
void Set_servo_reference(int val);

/**
 * @brief Get motor reference
 * @return Motor reference as an 16-bit integer
 */
int16_t Get_motor_reference(void);

/**
 * @brief Set motor reference
 * @param val Motor reference
 */
void Set_motor_reference(int16_t val);

/**
 * @brief Get motor position
 * @return Motor position as an 16-bit integer
 */
int16_t Get_motor_pos();

/**
 * @brief Set motor position
 * @param val Motor position
 */
void Set_motor_pos(int16_t val);

/**
 * @brief Set IR value
 * @param ir_value IR value as an integer
 */
void Set_ir_value(int ir_value);

/**
 * @brief Checks if IR value is less than a threshold defined in parameters.h
 * @return True (1) if ir is blocked, false (0) otherwise
 */
int Ir_is_blocked();

#endif
