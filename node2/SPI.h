#ifndef SPI_H
#define SPI_H

#include <stdint.h>
void SPI_Init(void);

uint8_t SPI_Transceive(uint8_t cData);
void SPI_chip_select(void);
void SPI_chip_deselect(void);
#endif
