#include "menu.h"
#include "oled.h"
#include <stdlib.h>
#include <string.h>
#include "run_oled.h"
#include <stdio.h>
#include "sram.h"
#include "Joy_state.h"


#define PAGE_LENGTH 14
#define PAGE_BUFFER_SIZE (PAGE_LENGTH + 1)

void menu_init() {
    oled_init();
}

Nodeptr init_node(Nodeptr prev, Nodeptr parent, char* text) {
    Nodeptr nodeptr = (Nodeptr) sram_malloc(sizeof(Node));
    if (strlen(text) > PAGE_LENGTH) {
        text[PAGE_LENGTH] = '\0';
    }
    nodeptr->text = (char*) sram_malloc(PAGE_BUFFER_SIZE);
    strcpy(nodeptr->text, text);

    nodeptr->prev = prev;
    nodeptr->parent = parent;
    nodeptr->next = NULL;
    nodeptr->child = NULL;
    nodeptr->func = NULL;

    return nodeptr;
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
    Nodeptr headptr = init_node(NULL, NULL, "Quickplay");
    headptr->func =

    Nodeptr secondptr = init_node(headptr, NULL, "Tournament");
    headptr->next = secondptr;

    return headptr;
}

Playerptr init_player(Playerptr prev, Playerptr next, char* name) {
    Playerptr playerptr = malloc(sizeof(Player));
    playerptr->name = strdup(name);
    playerptr->prev = prev;
    playerptr->next = next;
    return playerptr;
}

Playerptr init_players() {
    // denne tenker jeg at heller kan få info fra databasen til nettsiden
    Playerptr playerptr = malloc(sizeof(Player));
    playerptr->name = strdup("NoName");

    playerptr->next = init_player(playerptr, NULL, "Edmond");
    playerptr->next->next = init_player(playerptr->next, NULL, "Sigurd");
    playerptr->next->next->next =
        init_player(playerptr->next->next, NULL, "Ola");
    return playerptr;
}
