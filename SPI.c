#include <avr/io.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
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

#define DDR_SPI DDRB
#define DD_MOSI DDB5
#define DD_MISO DDB6
#define DD_SCK DDB7
#define SEND PB5
#define RECEIVE PB6

void SPI_Init(void) {
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK) | (1 << DDB4);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

uint8_t SPI_Transceive(uint8_t cData) {
        /* Start transmission */
    SPDR = cData;
        /* Wait for transmission complete */
    //printf("cData before: %c\n\r", cData);

    while(!(SPSR & (1<<SPIF)));
    //PORTB |= (1 << PB4);
    cData = SPDR;
    cData &= 0xff;
//    printf("cData after: "BYTE_TO_BINARY_PATTERN"\n\r", BYTE_TO_BINARY(cData));
    return cData;
}
