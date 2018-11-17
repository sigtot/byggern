#include "parameters.h"
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);

    MCUCR |= (1 << SRE);               // Enable external memory interface
    volatile char* memory = (char*)0;  // Start address for the SRAM
    uint16_t SRAM = 0x1800;
    uint16_t memory_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n\r");
    // rand() stores some internal state, so calling this function in a loop
    // will
    // yield different seeds each time (unless srand() is called before this
    // function)
    uint16_t seed = rand();
    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    for (uint16_t i = SRAM; i < SRAM + memory_size; i++) {
        uint8_t some_value = rand();
        memory[i] = some_value;
        uint8_t retreived_value = memory[i];
        if (retreived_value != some_value) {
            write_errors++;
        }
    }
    // Retrieval phase: Check that no values were changed during or after the
    // write phase
    srand(seed);  // reset the PRNG to the state it had before the write phase
    for (uint16_t i = SRAM; i < SRAM + memory_size; i++) {
        uint8_t some_value = rand();
        uint8_t retreived_value = memory[i];

        if (retreived_value != some_value) {
            printf(
                "Retrieval phase error: memory[%4d] = %02X (should be "
                "%02X)\n\r",
                i, retreived_value, some_value);
            retrieval_errors++;
        }
    }
    printf(
        "SRAM test completed with \n\r(%4d/%4d) errors in write phase and "
        "\n\r(%4d/%4d) errors in retrieval phase\n\r\n\r",
        write_errors, memory_size, retrieval_errors, memory_size);
    while (1)
        ;
    return 0;
}
