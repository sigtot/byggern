#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "fonts.h"
#include <avr/pgmspace.h>
#include <avr/io.h>
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

#define OLED_cmd 0x1000
#define OLED_data 0x1200

void oled_init() {
    MCUCR |= (1 << SRE); // Enable external memory interface

    volatile char *memory = (char *) 0;
    memory[OLED_cmd] = 0xae; // display off
    memory[OLED_cmd] = 0xa1; // segment remap
    memory[OLED_cmd] = 0xda; // common pads hardware: alternative
    memory[OLED_cmd] = 0x12;
    memory[OLED_cmd] = 0xc8; // common output scan direction:com63~com0
    memory[OLED_cmd] = 0xa8; // multiplex ration mode:63
    memory[OLED_cmd] = 0x3f;
    memory[OLED_cmd] = 0xd5; // display divide ratio/osc. freq. mode
    memory[OLED_cmd] = 0x80;
    memory[OLED_cmd] = 0x81; // contrast control
    memory[OLED_cmd] = 0x50;
    memory[OLED_cmd] = 0xd9; // set pre-charge period
    memory[OLED_cmd] = 0x21;
    memory[OLED_cmd] = 0x20; // Set Memory Addressing Mode
    memory[OLED_cmd] = 0x00;
    memory[OLED_cmd] = 0xdb; // VCOM deselect level mode
    memory[OLED_cmd] = 0x30;
    memory[OLED_cmd] = 0xad; // master configuration
    memory[OLED_cmd] = 0x00;
    memory[OLED_cmd] = 0xa4; // out follows RAM content
    memory[OLED_cmd] = 0xa6; // set normal display
    memory[OLED_cmd] = 0xaf; // display on
}

void oled_print_trash() {
    volatile char *memory = (char *) 0;
    for (uint16_t i = 0; i < 8 * 128; i++) {
        memory[OLED_data] = 0xff;
    }
}

void oled_print_dollar() {
    printf(BYTE_TO_BINARY_PATTERN"\n\r", BYTE_TO_BINARY(pgm_read_byte(&font8[3][0])));
}

void OLED_write_data(char c) {
    int char_pos = c + 32;

}
