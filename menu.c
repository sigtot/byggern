#include "menu.h"
#include "P_driver.h"
#include "oled.h"
#include <stdlib.h>
#include <string.h>

Nodeptr init_menu() {
    Nodeptr headptr = malloc(sizeof(Node));
    headptr->text = strdup("hei");

    headptr->next = init_node(headptr, NULL, "text");
    headptr->next->next = init_node(headptr->next, NULL, "other");

    return headptr;
}

Nodeptr init_node(Nodeptr prev, Nodeptr parent, char *text) {
    Nodeptr nodeptr = malloc(sizeof(Node));
    nodeptr->text = strdup(text);
    nodeptr->prev = prev;
    nodeptr->parent = parent;
    return nodeptr;
}

void print_menu(Nodeptr headptr, Nodeptr selectedptr) {
    int i = 0;
    while (headptr != NULL) {
        OLED_pos(i, 0);
        if (headptr == selectedptr) {
            OLED_print_char('>');
        }
        else {
            OLED_print_char(' ');
        }
        OLED_print(headptr->text);
        headptr = headptr->next;
        i++;
    }
}
