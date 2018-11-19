#ifndef MENU_H
#define MENU_H

typedef void (*function_pointer)();

typedef struct node* Nodeptr;

typedef struct node {
    char* text;
    Nodeptr next;
    Nodeptr prev;
    Nodeptr parent;
    Nodeptr child;
    function_pointer func;
} Node;

typedef struct player* Playerptr;

typedef struct player {
    char* name;
    int score;
    Playerptr next;
    Playerptr prev;
} Player;

Nodeptr init_menu();

/**
 * Initializes a menu node
 * @param  prev Previous menu node
 * @param  parent Parent node
 * @param  text   Text
 * @return        Pointer to the new node
 */
Nodeptr init_node(Nodeptr prev, Nodeptr parent, char* text);

Playerptr init_player(Playerptr prev, Playerptr next, char* name);
Playerptr init_players();

#endif
