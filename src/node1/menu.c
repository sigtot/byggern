#include "menu.h"
#include "multifunction.h"
#include "oled.h"
#include <stdlib.h>
#include <string.h>
#include <avr/delay.h>

Nodeptr init_menu() {
    Nodeptr headptr = malloc(sizeof(Node));
    headptr->text = strdup("Play Pinball");
    headptr->func = init_game;

    headptr->next = init_node(headptr, NULL, "Highscores");
    headptr->next->next = init_node(headptr->next, NULL, "Top 3");

    headptr->next->child = init_node(NULL, headptr, "Name:");
    headptr->next->child->next = init_node(headptr->child, headptr, "Sub 2");

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

void init_game() {
    printf("Init game\n\r");
}

function_pointer run_menu() {
    int should_update_menu = 1;
    Nodeptr headptr = init_menu();
    Nodeptr selectedptr = headptr;
    while(1) {
        _delay_ms(10);
        Joy_state joy_state = joy_get_state();
        motorbox_send_servo(Joy_state_get_servo_value(joy_state));
        switch(joy_state.dir) {
        case DOWN:
            if (selectedptr->next != NULL) {
                selectedptr = selectedptr->next;
                should_update_menu = 1;
            }
            break;
        case UP:
            if (selectedptr->prev != NULL) {
                selectedptr = selectedptr->prev;
                should_update_menu = 1;
            }
            break;
        case RIGHT:
            if (selectedptr->child != NULL) {
                headptr = selectedptr->child;
                selectedptr = selectedptr->child;
                should_update_menu = 1;
            }
            if (selectedptr->func != NULL) {
                selectedptr->func();
                should_update_menu = 1;
            }
            break;
        case LEFT:
            if (selectedptr->parent != NULL) {
                headptr = selectedptr->parent;
                selectedptr = selectedptr->parent;
                should_update_menu = 1;
            }
            break;
        }
        Button button_state = buttons_get_state();
        if (button_state.joy && (selectedptr->child != NULL)) {
            headptr = selectedptr->child;
            selectedptr = selectedptr->child;
            should_update_menu = 1;
        }

        if (should_update_menu) {
            print_menu(headptr, selectedptr);
            _delay_ms(300); // Wait a little after each interraction with GUI
            should_update_menu = 0;
        }

        if (button_state.right && (selectedptr->func != NULL)) {
            return selectedptr->func;
        }
    }
}