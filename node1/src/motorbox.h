/**
 * @file motorbox.h
 * Send motor, servo and solenoid values over CAN api
 */

#ifndef MOTORBOX_H
#define MOTORBOX_H

/**
 * Send servo value if servo value is different than previous servo values
 * @param servo_val Servo value to be sent
 */
void motorbox_send_servo_if_updated(int servo_val);

/**
 * Send motor value if motor value is different than previous motor values
 * @param motor_val Motor value to be sent
 */
void motorbox_send_motor_if_updated(int motor_val);

/**
 * Send solenoid signal if button value is updated
 * @param button_val The state of the button on the multifunctional board
 */
void motorbox_send_solenoid_if_kick(int button_val);

#endif
