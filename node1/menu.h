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

Nodeptr init_menu();
Nodeptr init_node(Nodeptr prev, Nodeptr parent, char *text);
void print_menu();

void init_game();

function_pointer run_menu();

#endif
