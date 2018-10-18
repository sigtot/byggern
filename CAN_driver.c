#include "CAN_driver.h"
#include "MCP2515.h"
#include <avr/io.h>



void CAN_LoopBack_Init() {

    SPI_Init();
    MCP2515_Reset();

    // Self-test
    char value = MCP2515_Read(MCP_CANSTAT);
    if((value & MODE_MASK)  != MODE_CONFIG) {
        printf("MCP2515 is NOT in configuration mode after reset!\n");
        return 1;
    }

    MCP2515_Write(MCP_CANCTRL, MODE_LOOPBACK);

}

void CAN_Message_Send(Message *message) {

    MCP2515_Bit_Modify(MCP_RXB0CTRL, (1 << 3), (1 << 3));
    MCP2515_Write(MCP_RXB0SIDH, 0);
    MCP2515_Bit_Modify(MCP_RXB0SIDL, (0x111 << 5), (1 << 5));
    MCP_RXB0SID
    for (int i=0;i<message->length; i++) {
        MCP2515_Write(0x66+i, message->data[i]);
    }
}

void CAN_Transmit_Complete();

void CAN_Data_Receive() {

}

void CAN_Int_Vect();
