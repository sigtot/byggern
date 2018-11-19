#ifndef OLED_PRINT_H
#define OLED_PRINT_H

#include "menu.h"

#include <stdint.h>
#include <stdlib.h>

void print_menu();
void print_game(uint8_t score);
void print_players(Playerptr headptr, Playerptr selectedptr);
void print_highscores();

#endif
