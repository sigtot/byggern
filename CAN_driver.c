#include "CAN_driver.h"
#include "MCP2515.h"
#include <avr/io.h>
#include <util/delay.h>

void CAN_LoopBack_Init() {
    printf(" (SPI Init)\n\r");
    SPI_Init();
    printf(" (Reset)\n\r");
    MCP2515_Reset();

    // Enable interrupt
    //printf("Enable interrupt");
    //CAN_INT_Enable();
    // Self-test
    //printf("(Read config)\n\r");
    char value = MCP2515_Read(MCP_CANSTAT);
    if((value & MODE_MASK)  != MODE_CONFIG) {
        printf("MCP2515 is NOT in configuration mode after reset! %x %x %x \n\r", value, MODE_MASK, MODE_CONFIG);
    }

    printf(" (Set loopback mode)\n\r");
    MCP2515_Write(MCP_CANCTRL, MODE_LOOPBACK);
    value = MCP2515_Read(MCP_CANSTAT);
    if((value & MODE_MASK)  == MODE_CONFIG) {
        printf("MCP2515 is in configuration mode after reset!\n");
    }
}

void CAN_Message_Send(Message *message) {
    //while(!(MCP_TXB0CTRL & (1 << 3))); // Wait for send to complete
    printf(" (Set data length)\n\r");
    MCP2515_Write(MCP_TXB0DLC, message->length);
    printf(" (Send ID higher)\n\r");
    MCP2515_Write(MCP_TXB0SIDH, 0);
    for (int i=0; i < message->length; i++) {
        printf(" (Write data %d)\n\r", i);
        MCP2515_Write(MCP_TXB0D0+i, message->data[i]);
        char loopback_data = MCP2515_Read(MCP_TXB0D0+i);
    }
        printf(" (Send ID lower)\n\r");
    MCP2515_Bit_Modify(MCP_TXB0SIDL, (0x111 << 5), (1 << 5));
    printf(" (Request to send)\n\r");
    MCP2515_Requst_To_Send();
}

void CAN_Transmit_Complete();

void CAN_Data_Receive() {
    DDRD &= ~(1 << PD2);
    while((PORTD & (1 << PD2))); // Wait for interrupt signal

    printf(" (Read data length)\n\r");
    char length = MCP2515_Read(MCP_RXB0DLC);
    printf("Read length %d in RX reg\n\r", length);
    for (int i = 0; i < length; i++) {
        char data = MCP2515_Read(MCP_TXB0D0+i);
        printf("%c", data);
    }
}

void CAN_INT_Enable() {
    //MCP2515_Bit_Modify(MCP_CANINTE, (1 << 2), (1 << 2));
    MCP2515_Bit_Modify(MCP_CANINTE, 1, 1);
}

void CAN_Int_Vect();
