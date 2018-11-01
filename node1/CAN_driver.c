#include "CAN_driver.h"
#include "MCP2515.h"
#include <avr/io.h>
#include <util/delay.h>

void CAN_LoopBack_Init() {
    SPI_Init();
    MCP2515_Reset();

    // Enable interrupt
    //printf("Enable interrupt");
    //CAN_INT_Enable();
    // Self-test
    //printf("(Read config)\n\r");
    _delay_ms(1);
    char value = MCP2515_Read(MCP_CANSTAT);
    if((value & MODE_MASK)  != MODE_CONFIG) {
        printf("MCP2515 is NOT in configuration mode after reset! %x %x %x \n\r", value, MODE_MASK, MODE_CONFIG);
    }

    MCP2515_Write(MCP_CANCTRL, MODE_LOOPBACK);
}

void CAN_Message_Send(Message *message) {
    //while(!(MCP_TXB0CTRL & (1 << 3))); // Wait for send to complete
    MCP2515_Write(MCP_TXB0DLC, message->length);
    MCP2515_Write(MCP_TXB0SIDH, 0);
    for (int i=0; i < message->length; i++) {
        MCP2515_Write(MCP_TXB0D0+i, message->data[i]);
    }
    MCP2515_Bit_Modify(MCP_TXB0SIDL, (0x111 << 5), (1 << 5)); // This is stupid
    MCP2515_Requst_To_Send();
}

void CAN_Transmit_Complete();

void CAN_Data_Receive(char *strarr) {
    _delay_ms(1);
    int length = MCP2515_Read(MCP_RXB0DLC);
    for (int i = 0; i < length; i++) {
        char data = MCP2515_Read(MCP_RXB0D0+i);
        strarr[i] = data;
    }
    strarr[length] = '\0';
}

void CAN_INT_Enable() {
    MCP2515_Bit_Modify(MCP_CANINTE, 1, 1);
}

void CAN_Int_Vect();
