#include "parameters.h"
#include "CAN_driver.h"
#include "MCP2515.h"
#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"
#include "MCP2515.h"


void CAN_init(char mode) {
    SPI_Init();
    MCP2515_Reset();
    CAN_INT_Enable();

    _delay_ms(1); // Very important delay
    char value = MCP2515_Read(MCP_CANSTAT);
    if((value & MODE_MASK)  != MODE_CONFIG) {
        printf("MCP2515 is NOT in configuration mode after reset! %02x %02x %02x But it doesn't matter :)\n\r", value, MODE_MASK, MODE_CONFIG);
    }

    MCP2515_Write(MCP_CANCTRL, mode);
}

void CAN_LoopBack_Init() {
    CAN_init(MODE_LOOPBACK);
}

void CAN_Normal_Init() {
    CAN_init(MODE_NORMAL);
}

void CAN_Message_Send(Message *message) {
    //while(!(MCP_TXB0CTRL & (1 << 3))); // Wait for send to complete
    MCP2515_Write(MCP_TXB0DLC, message->length);
    MCP2515_Write(MCP_TXB0SIDH, message->ID);
    for (int i=0; i < message->length; i++) {
        MCP2515_Write(MCP_TXB0D0+i, message->data[i]);
    }
    MCP2515_Requst_To_Send();
}

void CAN_Transmit_Complete();

void CAN_Data_Receive(char *strarr) {
	while(!(MCP_CANINTF & (1 << MCP_RX1IF)));
    _delay_ms(1);
    int length = MCP2515_Read(MCP_RXB1DLC);
    for (int i = 0; i < length; i++) {
        char data = MCP2515_Read(MCP_RXB1D0+i);
        strarr[i] = data;
    }
    strarr[length] = '\0';

	// Reset the interrupt flags
	MCP2515_Bit_Modify(MCP_CANINTF, (1 << 1), 0);
}

void CAN_Message_Receive(Message *message) {
	while(!(MCP_CANINTF & (1 << MCP_RX1IF)));
    _delay_ms(1);
    message->length = MCP2515_Read(MCP_RXB1DLC);
    message->ID = MCP2515_Read(MCP_RXB1SIDH);
    for (int i = 0; i < message->length; i++) {
        char data = MCP2515_Read(MCP_RXB1D0+i);
        message->data[i] = data;
    }
    message->data[message->length] = '\0';

	// Reset the interrupt flags
	MCP2515_Bit_Modify(MCP_CANINTF, (1 << 1), 0);
}
void CAN_INT_Enable() {
    // Set both receive buffers some reason
    MCP2515_Bit_Modify(MCP_CANINTE, (1 << 0), 0xff);
    MCP2515_Bit_Modify(MCP_CANINTE, (1 << 1), 0xff);
}

void CAN_Int_Vect();
