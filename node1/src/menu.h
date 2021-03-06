/**
 * @file menu.h
 * @brief menu initialization functions
 */

#ifndef MENU_H
#define MENU_H

#include "stdint.h"
#include "Joy_state.h"

typedef void (*function_pointer)();

typedef struct node* Nodeptr;

/**
 * @brief Struct containing node variables
 */
typedef struct node {
    char* text;
    Nodeptr next;
    Nodeptr prev;
    Nodeptr head;
    Nodeptr parent;
    Nodeptr child;
    function_pointer func;
} Node;

typedef struct player* Playerptr;

/**
 * @brief Struct containing player variables
 */
typedef struct player {
    char* name;
    int score;
    Playerptr next;
    Playerptr prev;
} Player;


/**
 * @brief initialization of the OLED menu
 */
void menu_init();

Nodeptr update_menu(Nodeptr selectedptr, Dir joy_dir);
Nodeptr init_create_main_menu();

/**
 * Initializes a menu node
 * @param  prev Pointer to previous menu node
 * @param  parent Pointer to parent node
 * @param  text Text
 * @return Pointer to the new node
 */
Nodeptr init_node(Nodeptr prev, Nodeptr parent, char* text, Nodeptr head);

/**
 * Initializes a Player
 * @param  prev Pointer to previous player
 * @param  next Pointer to next player
 * @param  name Player name
 * @return Pointer to the new player
 */
Playerptr init_player(Playerptr prev, Playerptr next, char* name);

/**
 * initialization of players
 */
Playerptr init_players();

#endif
