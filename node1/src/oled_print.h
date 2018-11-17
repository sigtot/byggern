#include "create_menus.h"

#include <stdint.h>
#include <stdlib.h>

#ifndef OLED_PRINT_H
#define OLED_PRINT_H

void print_test();
void print_menu();
void print_game(uint8_t score);
void print_players(Playerptr headptr, Playerptr selectedptr);
void print_highscores();


#endif
