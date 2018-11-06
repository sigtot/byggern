#include "joy_pos_receiver.h"
#include "../common/MCP2515.h"

/*
This logic should be added to the common Joystick.h file when it's made
*/

// Only prints the state at this time
void joy_pos_receive() {
    char msg[9];
	CAN_Data_Receive(&msg);
    printf("Joy pos received: %d %d %d\n\r", (int) msg[0], (int) msg[1], (Dir) msg[2]);
}
