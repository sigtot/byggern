#include "menu.h"
#include "oled.h"
#include <stdlib.h>
#include <string.h>
#include "menu_functions.h"
#include <stdio.h>
#include "sram.h"
#include "Joy_state.h"

#define PAGE_LENGTH 14
#define PAGE_BUFFER_SIZE (PAGE_LENGTH + 1)

void menu_init() {
    oled_init();
}

Nodeptr update_menu(Nodeptr selectedptr, Dir joy_dir) {
    switch (joy_dir) {
        case DOWN:
            if (selectedptr->next != NULL) {
                return selectedptr->next;
            }
        case UP:
            if (selectedptr->prev != NULL) {
                return selectedptr->prev;
            }
        case RIGHT:
            if (selectedptr->child != NULL) {
                return selectedptr->child;
            }
        case LEFT:
            if (selectedptr->parent != NULL) {
                return selectedptr->parent;
            }
        case NEUTRAL:
            return selectedptr;
    }
    return selectedptr;
}

Nodeptr init_create_main_menu() {
    Nodeptr headptr = init_node(NULL, NULL, "Quickplay", NULL);
    headptr->func = mfnc_play_game;
    headptr->head = headptr;

    Nodeptr secondptr = init_node(headptr, NULL, "Select player", headptr);

    Nodeptr thirdptr = init_node(secondptr, NULL, "Open web api", headptr);
    thirdptr->func = mfnc_open_web_api;

    Nodeptr fourthptr = init_node(thirdptr, NULL, "Highscores", headptr);
    fourthptr->func = mfnc_show_highscores;

    return headptr;
}

Nodeptr init_node(Nodeptr prev, Nodeptr parent, char* text, Nodeptr head) {
    Nodeptr nodeptr = (Nodeptr)sram_malloc(sizeof(Nodeptr));
    if (strlen(text) > PAGE_LENGTH) {
        text[PAGE_LENGTH] = '\0';
    }
    nodeptr->text = (char*)sram_malloc(PAGE_BUFFER_SIZE);
    strcpy(nodeptr->text, text);

    nodeptr->head = head;
    nodeptr->prev = prev;
    nodeptr->parent = parent;
    nodeptr->next = head;
    nodeptr->prev->next = nodeptr;
    head->prev = nodeptr;
    nodeptr->child = NULL;
    nodeptr->func = NULL;

    // nodeptr->prev->next = nodeptr;

    return nodeptr;
}

Playerptr init_player(Playerptr prev, Playerptr next, char* name) {
    Playerptr playerptr = sram_malloc(sizeof(Playerptr));
    if (strlen(name) > PAGE_LENGTH) {
        name[PAGE_LENGTH] = '\0';
    }
    playerptr->name = (char*)sram_malloc(PAGE_BUFFER_SIZE);
    strcpy(playerptr->name, name);
    playerptr->prev = prev;
    playerptr->next = next;
    playerptr->score = 0;
    return playerptr;
}

Playerptr init_players() {
    Playerptr playerOne = init_player(NULL, NULL, "Anonymous");

    Playerptr playerTwo = init_player(playerOne, NULL, "Edmond");
    playerOne->next = playerTwo;

    Playerptr playerThree = init_player(playerTwo, NULL, "Sigurd");
    playerTwo->next = playerThree;

    Playerptr playerFour = init_player(playerThree, NULL, "Ola");
    playerThree->next = playerFour;

    Playerptr playerFive = init_player(playerFour, NULL, "Jo Arve");
    playerFour->next = playerFive;

    Playerptr playerSix = init_player(playerFive, NULL, "Waseem");
    playerFive->next = playerSix;

    Playerptr playerSeven = init_player(playerSix, NULL, "Kolbjorn");
    playerSix->next = playerSeven;
    return playerOne;
}
