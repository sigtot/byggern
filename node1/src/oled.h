#ifndef OLED_H
#define OLED_H

#include <stdint.h>

void oled_init();
void OLED_clear_page(int page);
void OLED_clear();
void OLED_write_data(char c);
void OLED_reset();
void OLED_home();
void OLED_pos(uint8_t page, uint8_t column);
void OLED_print_char(char c);
void OLED_print(char* word);
void OLED_print_page(char* word, int page);

void OLED_set_page_address(int start_page, int end_page);
void OLED_set_column_address(uint8_t start_addr, uint8_t end_address);

#endif
