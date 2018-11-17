#include "create_menus.h"

Nodeptr init_test() {
    
}

Nodeptr init_menu() {

    Nodeptr headptr = malloc(sizeof(Node));
    headptr->text = strdup("Play Pinball");
    headptr->func = init_game;

    headptr->next = init_node(headptr, NULL, "Highscores");
    headptr->next->func = show_highscores;

    headptr->next->next = init_node(headptr->next, NULL, "Select Player");
    headptr->next->next->func = print_players;

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
