/**
 * @file can_api.h
 * @brief Sends a CAN message from Node 1
 */
#ifndef CAN_API_H
#define CAN_API_H

/**
 * Initialization of CAN application programming interface
 * note: interrupts enabled
 */
void can_api_init();

/**
 * Send message over CAN bus
 * @param ID one byte message ID 
 * @param servo_val Data to be sendt
 * @param length Data length
 */
void can_message_send(char ID, int servo_val, int length);

#endif
