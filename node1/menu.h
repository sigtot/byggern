#ifndef MENU_H
#define MENU_H



typedef struct node *Nodeptr;

typedef struct node {

    char *text;
    Nodeptr next;
    Nodeptr prev;
    Nodeptr parent;
    Nodeptr child;
} Node;

Nodeptr init_menu();
Nodeptr init_node(Nodeptr prev, Nodeptr parent, char *text);
void print_menu();


#endif
