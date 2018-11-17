#include "create_menus.h"
#include "oled.h"
#include <stdlib.h>
#include <string.h>
#include "run_oled.h"
#include <stdio.h>



Nodeptr init_test_menu() {
    Nodeptr headptr = init_node(NULL, NULL, "node11");
    Nodeptr secondptr = init_node(headptr, NULL, "node12");
    headptr->next = secondptr;
    Nodeptr child = init_node(NULL, secondptr, "node22");
    secondptr->child = child;
    child -> func = test_function;

    return headptr;
}

Nodeptr init_menu() {

    Nodeptr headptr = malloc(sizeof(Node));
    headptr->text = strdup("Play Pinball");
    //headptr->func = run_game;

    headptr->next = init_node(headptr, NULL, "Highscores");
    //headptr->next->func = run_highscores;

    headptr->next->next = init_node(headptr->next, NULL, "Select Player");
    //headptr->next->next->func = run_playerlist;

    headptr->next->next->next =
        init_node(headptr->next->next, NULL, "Settings");
    headptr->next->next->next->child = init_node(
        headptr->next->next->next, headptr->next->next->next, "Sound");
    headptr->next->next->next->child->next =
        init_node(headptr->next->next->next->child, headptr->next->next->next,
                  "setting2");
    headptr->next->next->next->child->next->next =
        init_node(headptr->next->next->next->child->next,
                  headptr->next->next->next, "setting3");
    return headptr;
}

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
