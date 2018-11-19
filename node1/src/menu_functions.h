/**
 * @file menu_functions.h
 * @brief Contains functions which can be executed form the menu
 */
#ifndef MENU_FUNCTIONS_H
#define MENU_FUNCTIONS_H
#include "menu.h"
#include <stdio.h>

typedef struct Current_game {
    char *player;
    int score;
    int playing;
} Current_game;

/**
 * Starts the ping pong game
 */
void mfnc_play_game();

void init_current_game();

void set_score(uint8_t score);

#endif
