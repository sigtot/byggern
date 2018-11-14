#ifndef MENU_H
#define MENU_H

typedef void (*function_pointer)();

typedef struct node *Nodeptr;

typedef struct node {

    char *text;
    Nodeptr next;
    Nodeptr prev;
    Nodeptr parent;
    Nodeptr child;
    function_pointer func;
} Node;

typedef struct player *Playerptr;

typedef struct player {
    char *name;
    int score;
    Playerptr next;
    Playerptr prev;
} Player;


Nodeptr init_menu();
Nodeptr init_node(Nodeptr prev, Nodeptr parent, char *text);

Playerptr init_player(Playerptr prev, Playerptr next, char *name);
Playerptr init_players();

void print_menu();
void init_game();
void print_players(Playerptr headptr, Playerptr selectedptr);
void show_highscores();

void run_menu();

#endif
