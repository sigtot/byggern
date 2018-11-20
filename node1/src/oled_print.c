#include "parameters.h"
#include "oled_print.h"
#include "oled.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <stdlib.h>

void print_menu(Nodeptr selectedptr) {
    Nodeptr printptr = selectedptr;
    while (printptr != printptr->head) {
        printptr = printptr->prev;
    }
    OLED_clear();
    int i = 0;
    while (1) {
        OLED_pos(i, 0);
        if (printptr == selectedptr) {
            OLED_print_char('>');
        } else {
            OLED_print_char(' ');
        }
        OLED_print(printptr->text);
        if (printptr->child != NULL) {
            OLED_print_char('>');
        }
        printptr = printptr->next;
        i++;
        if (printptr == printptr->head) {
            break;
        }
    }
    _delay_ms(300);
}

void print_game(Playerptr playerptr) {
    uint8_t score = playerptr->score;
    char *temp;
    OLED_clear();
    OLED_print(strdup("-GAME IS ACTIVE-"));
    OLED_print(strdup("|             |"));
    OLED_print(sprintf(temp, "|    %-3d    |", score));
    OLED_print(strdup("|             |"));
    OLED_print(strdup("|             |"));
    OLED_print(strdup("|             |"));
    OLED_print(strdup("|             |"));
    OLED_print(strdup("|_____________|"));
    // just checking if it appears as should
    printf("Init game\n\r");
}

void print_players(Playerptr playerptr) {
    OLED_clear();
    int i = 0;
    Playerptr selected_player = playerptr;
    while (selected_player->prev != NULL) {
        selected_player = selected_player->prev;
    }
    while (selected_player->next != NULL) {
        OLED_pos(i, 0);
        if (selected_player == playerptr) {
            OLED_print_char('>');
        } else {
            OLED_print_char(' ');
        }
        OLED_print(selected_player->name);
        selected_player = selected_player->next;
        i++;
    }
}

void print_highscores(Playerptr playerptr) {
    oled_init();
    OLED_clear();
    

    OLED_print(strdup("---HIGHSCORES---"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|______________|"));
}
