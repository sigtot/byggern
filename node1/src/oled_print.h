#ifndef OLED_PRINT_H
#define OLED_PRINT_H

#include "menu.h"

#include <stdint.h>
#include <stdlib.h>

void print_menu();
void print_game(Playerptr playerptr);
void print_players(Playerptr playerptr);
void print_highscores(Playerptr playerptr);

#endif
