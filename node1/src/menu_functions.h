/**
 * @file menu_functions.h
 * @brief Contains functions which can be executed from the menu
 */
#ifndef MENU_FUNCTIONS_H
#define MENU_FUNCTIONS_H
#include "menu.h"
#include <stdio.h>
#include <stdint.h>

typedef struct Current_game {
    Playerptr selected_player;
    uint8_t fails;
} Current_game;

void mfnc_play_game(Nodeptr selectedptr);
void mfnc_show_highscores(Nodeptr selectedptr);
void mfnc_select_player();
void mfnc_open_web_api(Nodeptr selectedptr);
void init_current_game();

void set_fails(uint8_t score);
uint8_t get_fails();

#endif
