#include <avr/io.h>
#include "parameters.h"

void SPI_Init(void) {
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1 << DD_CS)|(1 << DD_SS);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_chip_select(void) {
    PORTB &= ~(1 << CS);
}

void SPI_chip_deselect(void) {
    PORTB |= (1 << CS);
}

uint8_t SPI_Transceive(uint8_t cData) {
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
    cData = SPDR;
    cData &= 0xff;

    return cData;
}
