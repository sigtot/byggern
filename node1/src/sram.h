#ifndef SRAM_H
#define SRAM_H
#include <stdlib.h>
#include <stdint.h>

void sram_init();
uint8_t *sram_malloc(size_t size);
void sram_free(uint8_t *);

#endif
