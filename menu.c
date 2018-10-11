#include "menu.h"
#include "P_driver.h"
#include "oled.h"
#include <stdlib.h>
#include <string.h>

Nodeptr init_menu() {
    Nodeptr headptr = malloc(sizeof(Node));
    headptr->text = strdup("Top 1");

    headptr->next = init_node(headptr, NULL, "Top 2");
    headptr->next->next = init_node(headptr->next, NULL, "Top 3");

    headptr->child = init_node(NULL, headptr, "Sub 1");
    headptr->child->next = init_node(headptr->child, headptr, "Sub 2");

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
    OLED_clear();
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
        if (headptr->child != NULL) {
            OLED_print_char('>');
        }
        headptr = headptr->next;
        i++;
    }
}
