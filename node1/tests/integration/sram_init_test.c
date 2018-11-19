#include "parameters.h"
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "sram.h"
#include "uart.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);

    printf("Initializing SRAM...\n\r");
    sram_init();
    printf("SRAM successfully initialized. Printing the 20 first bytes: \n\r");

    volatile uint8_t* sram = (uint8_t*)SRAM_ADDRESS;
    for (int i = 0; i < 20; i++) {
        printf("%2x ", sram[i]);
    }

    printf("\n\rSRAM init test finished.\n\r");
    while (1)
        ;
    return 0;
}
