
/**
 * @file oled_print.h
 * Printing on the OLED
 */

#ifndef OLED_PRINT_H
#define OLED_PRINT_H

#include "menu.h"

#include <stdint.h>
#include <stdlib.h>

/**
 * Printing main menu
 */
void print_menu();

/**
 * Printing game screen
 * @param score 
 */
void print_game(uint8_t score);

/**
 * Printing players
 * @param headptr Playerptr to the head of the linked list
 * @param selectedptr Playerptr to
 */
void print_players(Playerptr headptr, Playerptr selectedptr);
void print_highscores();

#endif
