#include "sram.h"
#include "parameters.h"
#include <avr/io.h>
#include <limits.h>



#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                    \
    (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'),   \
    (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'),   \
    (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'),   \
    (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')


/**
 * @brief Initialize sram
 * The first NUM_BLOCKS bits in the SRAM correspond to the block indexes that
 * have already been allocated. A 1 signifies an occupied block and 0 a free one.
 */
void sram_init() {
    MCUCR |= (1 << SRE); // Enable external memory interface

    volatile uint8_t* sram = (uint8_t*)SRAM_ADDRESS;
    int num_blocks = SRAM_MEM_SIZE / SRAM_BLOCK_SIZE;
    int num_header_bytes = 2 * num_blocks / CHAR_BIT;

    int i;
    for (i = 0; i < num_header_bytes; i++) {
        sram[i] = 0;
    }
    for (i = 0; i < num_header_bytes / SRAM_BLOCK_SIZE - 1; i++) {
        sram[i / CHAR_BIT] |= (1 << (CHAR_BIT - (i % CHAR_BIT) - 1));
    }
    sram[i / CHAR_BIT] &= ~(1 << (CHAR_BIT - (i % CHAR_BIT) - 1));
}

uint8_t * sram_malloc(size_t size) {
    volatile uint8_t* sram = (uint8_t*)SRAM_ADDRESS;
    int num_header_bits = 2 * SRAM_MEM_SIZE / SRAM_BLOCK_SIZE;
    int fcbc = -1; // Free consecutive block counter
    int i;
    for (i = 0; i < num_header_bits; i++) {
        if (!(sram[i / CHAR_BIT] & (1 << (CHAR_BIT - (i % CHAR_BIT) - 1)))) {
            fcbc++;

            if (fcbc >= size * 2) {
                i++;
                break;
            }
        } else {
            fcbc = -1;
        }
    }
    //set allocated in index bits
    if (fcbc >= size*2) {
        for (int j = i - fcbc; j < i - fcbc + fcbc/SRAM_BLOCK_SIZE + 1; j++) {
            sram[j / CHAR_BIT] |= (1 << (CHAR_BIT - (j % CHAR_BIT) -1));
        }
        sram[(i/2) / CHAR_BIT] &= ~(1 << (CHAR_BIT - (i % CHAR_BIT) - 1));
    }
    if (fcbc < 2 * size) {
        return NULL;
    }
    printf("returning pointer to sram[%d]\n\r", (i-fcbc)/2 * SRAM_BLOCK_SIZE);
    return &sram[(i - fcbc) / 2 * SRAM_BLOCK_SIZE ];
}

void sram_free(uint8_t *memory) {
}
