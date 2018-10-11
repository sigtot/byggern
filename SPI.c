#include <avr/io.h>

#define DDR_SPI DDRB
#define DD_MOSI DDB5
#define DD_MISO DDB6
#define DD_SCK DDB7
#define SEND PB5
#define RECEIVE PB6

void SPI_MasterInit(void) {
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK) | (1 << PB4);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char cData) {
    //PORTB &= ~(1 << PB4);

        /* Start transmission */
    SPDR = cData;
        /* Wait for transmission complete */
    printf("cData before: %c\n\r", cData);

    while(!(SPSR & (1<<SPIF)));
    //PORTB |= (1 << PB4);
    cData = SPDR;
    printf("cData after: %c\n\r", cData);
}

void SPI_SlaveInit(void)
{
/* Set MISO output, all others input */
DDR_SPI = (1<<DD_MISO);
/* Enable SPI */
SPCR = (1<<SPE);
}

char SPI_SlaveReceive(void)
{
    /* Wait for reception complete */
    //PORTB &= ~(1 << PB4);
    while(!(SPSR & (1<<SPIF)));
    char out = SPDR;
    //PORTB |= (1 << PB4);
    /* Return data register */
    return out;
}
