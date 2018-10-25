#include "CAN_driver.h"
#include "MCP2515.h"
#include <avr/io.h>

#define BBP "%c%c%c%c%c%c%c%c%c%c%c%c"
#define BB(byte)  \
    (byte & 0x800 ? '1' : '0'), \
    (byte & 0x400 ? '1' : '0'), \
    (byte & 0x200 ? '1' : '0'), \
    (byte & 0x100 ? '1' : '0'), \
    (byte & 0x80 ? '1' : '0'), \
    (byte & 0x40 ? '1' : '0'), \
    (byte & 0x20 ? '1' : '0'), \
    (byte & 0x10 ? '1' : '0'), \
    (byte & 0x08 ? '1' : '0'), \
    (byte & 0x04 ? '1' : '0'), \
    (byte & 0x02 ? '1' : '0'), \
    (byte & 0x01 ? '1' : '0')


void CAN_LoopBack_Init() {
    printf(" (SPI Init)\n\r");
    SPI_Init();
    printf(" (Reset)\n\r");
    MCP2515_Reset();
    MCP2515_Write(MCP_CANCTRL, MODE_CONFIG);

    // Enable interrupt
    //printf("Enable interrupt");
    //CAN_INT_Enable();
    // Self-test
    //printf("(Read config)\n\r");
    char value = MCP2515_Read(MCP_CANSTAT);
    if((value & MODE_MASK)  != MODE_CONFIG) {
        printf("MCP2515 is NOT in configuration mode after reset! "BBP" "BBP" "BBP"\n\r", BB(value), BB(MODE_MASK), BB(MODE_CONFIG));
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
    for (int i=0;i<message->length; i++) {
        printf(" (Write data %d)\n\r", i);
        MCP2515_Write(0x66+i, message->data[i]);
        char loopback_data = MCP2515_Read(0x66+i);
    }
    printf(" (Send ID higher)\n\r");
    MCP2515_Write(MCP_TXB0SIDH, 0);
    printf(" (Send ID lower)\n\r");
    MCP2515_Bit_Modify(MCP_TXB0SIDL, (0x111 << 5), (1 << 5));
    printf(" (Request to send)\n\r");
    MCP2515_Requst_To_Send();
}

void CAN_Transmit_Complete();

void CAN_Data_Receive() {
    PORTD &= ~(1 << PD2);
    while((PORTD & (1 << PD2))); // Wait for interrupt signal

    printf(" (Read data length)\n\r");
    char length = MCP2515_Read(MCP_RXB0DLC);
    printf("Read length %d in RX reg\n\r", length);
    for (int i = 0; i < length; i++) {
        printf(" (Read data %d)\n\r", i);
        char data = MCP2515_Read(0x66+i);
        printf("Read %c in RX reg\n\r", data);
    }
}

void CAN_INT_Enable() {
    //MCP2515_Bit_Modify(MCP_CANINTE, (1 << 2), (1 << 2));
    MCP2515_Bit_Modify(MCP_CANINTE, 1, 1);
}

void CAN_Int_Vect();
