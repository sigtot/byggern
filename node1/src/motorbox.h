#ifndef MOTORBOX_H
#define MOTORBOX_H

void motorbox_send_servo_if_updated(int servo_val);
void motorbox_send_motor_if_updated(int motor_val);
void motorbox_send_solenoid_if_kick(int button_val);

#endif
