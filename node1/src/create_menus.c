#include "create_menus.h"
#include "oled.h"
#include <stdlib.h>
#include <string.h>
#include "run_oled.h"
#include <stdio.h>

Nodeptr init_node(Nodeptr prev, Nodeptr parent, char* text) {
    Nodeptr nodeptr = malloc(sizeof(Node));
    nodeptr->text = strdup(text);
    nodeptr->prev = prev;
    nodeptr->parent = parent;
    return nodeptr;
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
