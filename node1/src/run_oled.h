#include "create_menus.h"

#include <stdio.h>

#ifndef MENU_H
#define MENU_H

uint8_t check_joystick_state();
function_pointer run_test();
void run_menu();
function_pointer run_game();
function_pointer run_highscores();
function_pointer run_playerlist();

#endif
