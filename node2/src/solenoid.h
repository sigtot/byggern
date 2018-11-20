/**
 * @file solenoid.h
 * @brief generates a solenoid kick (pulse)
 */
#ifndef SOLENOID_H
#define SOLENOID_H

/**
 * @brief initialization of solenoid, i.e. setting pulse output pin
 */
void solenoid_init();

/**
 * @brief generates an output on a pin imitating a pulse
 */
void solenoid_send_kick(void);

#endif
