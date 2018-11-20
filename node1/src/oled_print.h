/**
 * @file oled_print.h
 * @brief This file contains printer functions that hold the graphical print
 * logic
 */

#ifndef OLED_PRINT_H
#define OLED_PRINT_H

#include "menu.h"

#include <stdint.h>
#include <stdlib.h>

/**
 * Print main menu
 * @param selectedptr Any Nodeptr in the linked list
 */
void print_menu(Nodeptr selectedptr);

/**
 * Print game screen
 * @param playerptr The currently playing user 
 */
void print_game(Playerptr playerptr);

/**
 * Print players and their scores
 * @param playerptr The topmost player in the linked list
 */
void print_highscores(Playerptr playerptr);

/**
 * Print highscores
 * @param playerptr 
 */
void print_players(Playerptr playerptr);

/**
 * Prints the api enabled message
 */
void print_api_enabled();

#endif
