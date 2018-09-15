#include <stdlib.h>
#include <stdint.h>

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

#include <avr/io.h>

void SRAM_test(void)
{
  volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
  uint16_t ext_ram_size = 0x800;
  uint16_t write_errors = 0;
  uint16_t retrieval_errors = 0;
  printf("Starting SRAM test...\n\r");
  // rand() stores some internal state, so calling this function in a loop will
  // yield different seeds each time (unless srand() is called before this function)
  uint16_t seed = rand();
  // Write phase: Immediately check that the correct value was stored
  srand(seed);
  for (uint16_t i = ext_ram_size; i < 2 * ext_ram_size; i++) {
    uint8_t some_value = rand();
    ext_ram[i] = some_value;
    uint8_t retreived_value = ext_ram[i];

    if (retreived_value != some_value) {
      //printf("Write phase error: ext_ram[%4d] = %02X/%02X\n\r", i, retreived_value, some_value);
      write_errors++;
    } else {
      //printf("Correct at "BYTE_TO_BINARY_PATTERN"! (%02X/%02X/%02X)\n\r", BYTE_TO_BINARY(i), retreived_value, some_value, i);
      //printf("Correct value!!!!: ext_ram[%03X] = %02X/%02X\n\r", i,
      //  retreived_value, some_value);
    }
    /*
    if (retreived_value == (i & 0xFF)) {
      printf("Matches address: %02X:%02X (sent %02X)\n\r", i, retreived_value, some_value);
    } else {
      printf("Does not match!: %02X:%02X (sent %02X)\n\r", i, retreived_value, some_value);
    }
    */
 }
 // Retrieval phase: Check that no values were changed during or after the write phase
 srand(seed); // reset the PRNG to the state it had before the write phase
 for (uint16_t i = ext_ram_size; i < 2 * ext_ram_size; i++) {
   uint8_t some_value = rand();
   uint8_t retreived_value = ext_ram[i];
   if (retreived_value != some_value) {
     //printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n\r",
    //i, retreived_value, some_value);
     retrieval_errors++;
   }
 }
 printf("SRAM test completed with \n\r(%4d/%4d) errors in write phase and \n\r(%4d/%4d) errors in retrieval phase\n\r\n\r",
    write_errors,
    ext_ram_size,
    retrieval_errors,
    ext_ram_size);
}
