/**
 * @file oled_print.h
 * @brief This file contains printer functions that contain the graphical print
 * logic
 */
#ifndef OLED_PRINT_H
#define OLED_PRINT_H

#include "menu.h"

#include <stdint.h>
#include <stdlib.h>

void print_menu(Nodeptr menu_selectedptr);
void print_game(Playerptr playerptr);
void print_players(Playerptr playerptr);
void print_highscores(Playerptr playerptr);
void print_api_enabled();

#endif
