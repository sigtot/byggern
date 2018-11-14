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
    headptr->next->func = show_highscores;

    headptr->next->next = init_node(headptr->next, NULL, "Select Player");
    headptr->next->next->func = select_player;

    headptr->next->next->next = init_node(headptr->next->next, NULL, "Settings");
    headptr->next->next->next->child = init_node(
        headptr->next->next->next, headptr->next->next->next, "Sound");
    headptr->next->next->next->child->next = init_node(
        headptr->next->next->next->child, headptr->next->next->next, "setting2");
    headptr->next->next->next->child->next->next = init_node(
        headptr->next->next->next->child->next, headptr->next->next->next, "setting3");
    return headptr;
}

Playerptr init_players() {
    //denne tenker jeg at heller kan få info fra databasen til nettsiden
    Playerptr playerptr = malloc(sizeof(Player));
    playerptr->name = strdup("NoName");

    playerptr->next = init_player(playerptr, NULL, "Edmond");
    playerptr->next->next = init_player(playerptr->next, NULL, "Sigurd");
    playerptr->next->next->next = init_player(playerptr->next->next, NULL, "Ola");
    return playerptr
}

Nodeptr init_node(Nodeptr prev, Nodeptr parent, char *text) {
    Nodeptr nodeptr = malloc(sizeof(Node));
    nodeptr->text = strdup(text);
    nodeptr->prev = prev;
    nodeptr->parent = parent;
    return nodeptr;
}

Playerptr init_player(Playerptr prev, Playerptr next, char *name) {
    Playerptr playerptr = malloc(sizeof(Player));
    playerptr->name = strdup(name);
    playerptr->prev = prev;
    playerptr->next = next;
    return playerptr
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

void select_player() {
    printf("Select player");
}


void init_game() {
    uint8_t score = 0;
    OLED_print(strdup("-GAME IS ACTIVE-"));
    OLED_print(strdup("|              |"));
    char *temp;
    //the following ifs print according to numbers in score
    if (score < 10) {
        OLED_print(sprintf(a, "|  Score: %d    |", score));
    }
    else if (score > 10 && score < 100) {
        OLED_print(sprintf(a, "|  Score: %d   |", score));
    }
    else {
        OLED_print(sprintf(a, "|  Score: %d  |", score));
    }
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|______________|"));
    //just checking if it appears as should
    _delay_ms(5000);
    printf("Init game\n\r");
}

void show_highscores() {
    //needs a playerlist as input
    OLED_print(strdup("---HIGHSCORES---"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|______________|"));
    _delay_ms(5000);
}

void run_menu() {
    int should_update_menu = 1;
    Nodeptr headptr = init_menu();
    Nodeptr selectedptr = headptr;
    Playerptr playerptr = init_players();
    Playerptr selected_player = playerptr;
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
    }
}
