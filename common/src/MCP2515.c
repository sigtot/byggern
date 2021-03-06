#include "MCP2515.h"
#include <avr/io.h>
#include "SPI.h"

char transceive(char cData) {
    return SPI_Transceive(cData);
}

char MCP2515_Read(char address) {
    SPI_chip_select();
    SPI_Transceive(MCP_READ);
    SPI_Transceive(address);
    char data = SPI_Transceive(address);

    SPI_chip_deselect();
    return data;
}

void MCP2515_Write(char address, char data) {
    SPI_chip_select();
    SPI_Transceive(MCP_WRITE);
    SPI_Transceive(address);
    SPI_Transceive(data);

    SPI_chip_deselect();
}

void MCP2515_Requst_To_Send() {
    SPI_chip_select();

    // Denne kan kalles for 3 individuelle registre eller alle
    SPI_Transceive(MCP_RTS_TX0);
    SPI_chip_deselect();
}

char MCP2515_Read_Status() {
    SPI_chip_select();

    SPI_Transceive(MCP_READ_STATUS);
    char status = SPI_Transceive('a');
    return status;

    SPI_chip_deselect();
}

void MCP2515_Bit_Modify(char address, char mask, char data) {
    SPI_chip_select();

    SPI_Transceive(MCP_BITMOD);
    SPI_Transceive(address);
    SPI_Transceive(mask);
    SPI_Transceive(data);

    SPI_chip_deselect();
}

void MCP2515_Reset() {
    SPI_chip_select();

    SPI_Transceive(MCP_RESET);

    SPI_chip_deselect();
}
