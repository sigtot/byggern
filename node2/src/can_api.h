/**
 * @file can_api.h
 * @brief Sends a CAN message from Node 2
 */

#ifndef CAN_API_H
#define CAN_API_H

/**
 * Initialize the can API utilising the CAN normal init routine
 * and select INT0 as interrupt pin
 */
void can_api_init();

/**
 * Send a message of type integer over the CAN bus interface
 * @param ID  Message ID of one byte for prioritization
 * @param value  The message data
 * @param length The message length
 */
void can_api_value_send(char ID, int value, int length);

#endif
