#include "MCP2515.h"
#include <avr/io.h>


char MCP2515_Read(char address) {
    PORTB &= ~(1 << PB4);

    SPI_Transceive(MCP_READ);
    SPI_Transceive(address);
    char data = SPI_Transceive(address);

    PORTB |= (1 << PB4);
    return data;
}

void MCP2515_Write(char address, char data) {
    PORTB &= ~(1 << PB4);

    SPI_Transceive(MCP_WRITE);
    SPI_Transceive(address);
    SPI_Transceive(data);

    PORTB |= (1 << PB4);
}

void MCP2515_Requst_To_Send_All() {
    PORTB &= ~(1 << PB4);

    //Denne kan kalles for 3 individuelle registre eller alle
    SPI_Transceive(MCP_RTS_ALL);
    PORTB |= (1 << PB4);
}

char MCP2515_Read_Status() {
    PORTB &= ~(1 << PB4);

    SPI_Transceive(MCP_READ_STATUS);
    char status = SPI_Transceive('a');
    return status;

    PORTB |= (1 << PB4);

}

void MCP2515_Bit_Modify(char address, char mask, char data) {
    PORTB &= ~(1 << PB4);

    SPI_Transceive(MCP_BITMOD);
    SPI_Transceive(address);
    SPI_Transceive(mask);
    SPI_Transceive(data);

    PORTB |= (1 << PB4);
}

void MCP2515_Reset() {
    PORTB &= ~(1 << PB4);

    SPI_Transceive(MCP_RESET);

    PORTB |= (1 << PB4);
}
