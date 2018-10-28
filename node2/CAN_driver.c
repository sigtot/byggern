#include "CAN_driver.h"
#include "MCP2515.h"
#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"
#include "MCP2515.h"

void CAN_LoopBack_Init() {
    SPI_Init();
    printf("SPI initiated\n\r");
    MCP2515_Reset();
    printf("MCP reset\n\r");

    // Enable interrupt
    //printf("Enable interrupt");
    //CAN_INT_Enable();
    // Self-test
    //printf("(Read config)\n\r");
    char value = MCP2515_Read(MCP_CANSTAT);
    printf("MCP canstat read\n\r");
    if((value & MODE_MASK)  != MODE_CONFIG) {
        printf("MCP2515 is NOT in configuration mode after reset! %x %x %x \n\r", value, MODE_MASK, MODE_CONFIG);
    }

    MCP2515_Write(MCP_CANCTRL, MODE_LOOPBACK);
    value = MCP2515_Read(MCP_CANSTAT);
}

void CAN_Message_Send(Message *message) {
    //while(!(MCP_TXB0CTRL & (1 << 3))); // Wait for send to complete
    MCP2515_Write(MCP_TXB0DLC, message->length);
    MCP2515_Write(MCP_TXB0SIDH, 0);
    for (int i=0; i < message->length; i++) {
        MCP2515_Write(MCP_TXB0D0+i, message->data[i]);
    }
    MCP2515_Bit_Modify(MCP_TXB0SIDL, (0x111 << 5), (1 << 5));
    MCP2515_Requst_To_Send();
}

void CAN_Transmit_Complete();

void CAN_Data_Receive(char *strarr) {
    DDRD &= ~(1 << PD2);
    while((PORTD & (1 << PD2))); // Wait for interrupt signal
    _delay_ms(1);
    int length = MCP2515_Read(MCP_RXB0DLC);
    for (int i = 0; i < length; i++) {
        char data = MCP2515_Read(MCP_TXB0D0+i);
        strarr[i] = data;
    }
    strarr[length] = '\0';
}

void CAN_INT_Enable() {
    MCP2515_Bit_Modify(MCP_CANINTE, 1, 1);
}

void CAN_Int_Vect();
