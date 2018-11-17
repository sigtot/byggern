#include "create_menus.h"

#ifndef MENU_H
#define MENU_H

uint8_t check_joystick_state();
function_pointer run_menu();
function_pointer run_game();
function_pointer run_highscores();
function_pointer run_playerlist();

#endif
