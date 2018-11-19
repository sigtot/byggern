/**
 * @file sram.h
 * @brief Handles dynamic allocation of memory on the SRAM
 */
#ifndef SRAM_H
#define SRAM_H
#include <stdlib.h>
#include <stdint.h>


/**
 * @brief Initialize sram
 * The first NUM_BLOCKS bits in the SRAM correspond to the block indexes that
 * have already been allocated. A 1 signifies an occupied block and 0 a free
 * one.
 */
void sram_init();

/**
 * @brief Allocate memory on the SRAM
 * @param  size number of bytes to be allocated
 * @return      pointer to the allocated memory
 */
uint8_t* sram_malloc(size_t size);
void sram_free(uint8_t*);

#endif
