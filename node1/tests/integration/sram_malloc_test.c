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
    printf("SRAM successfully initialized. Testing sram_malloc \n\r");


    volatile char* sram = (char*)SRAM_ADDRESS;

    for (int i = 0; i < 128; i++) {
        printf("%2x ", sram[i]);
        if (!((i + 1) % 16)) {
            printf("\n\r");
        }
    }
    uint8_t* byteptr = sram_malloc(1);
    *byteptr = 5;
    char* textptr = sram_malloc(22);
    *textptr = "text";
    char* secondtest = sram_malloc(34);
    printf("block 5 before: %02x\n\r", *secondtest);
    strcpy(secondtest, "foo");
    printf("block 5 after: %s\n\r", secondtest);

    uint8_t ***ptr = &secondtest;
    printf("index of secondtest: %p\n\r", secondtest);

    for (int i = 0; i < 128; i++) {
        printf("%02x ", sram[i]);
        if (!((i + 1) % 16)) {
            printf("\n\r");
        }
    }

    printf("secondtest: %s\n\r", &sram[64]);

    printf("\n\rSRAM init test finished.\n\r");
    while (1)
        ;
    return 0;
}
