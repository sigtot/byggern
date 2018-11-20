#include "parameters.h"
#include "oled_print.h"
#include "oled.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

void print_menu(Nodeptr selectedptr) {
    Nodeptr printptr = selectedptr;
    while (printptr->prev != NULL) {
        printptr = printptr->prev;
    }
    OLED_clear();
    int i = 0;
    while (printptr != NULL) {
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
    }

    _delay_ms(300);
}

void print_game(Playerptr playerptr) {
    uint8_t score = playerptr->score;
    char *temp;
    OLED_clear();
    OLED_print(strdup("-GAME IS ACTIVE-"));
    OLED_print(strdup("|              |"));
    OLED_print(sprintf(temp, "|   %-3d   |", score));
    // the following ifs print according to numbers in score
    // TODO: Use printf("|%-10s|", "Hello");
    // https://stackoverflow.com/questions/276827/string-padding-in-c
    /*
    if (score < 10) {
        OLED_print(sprintf(temp, "|  Score: %d    |", score));
    } else if (score > 10 && score < 100) {
        OLED_print(sprintf(temp, "|  Score: %d   |", score));
    } else {
        OLED_print(sprintf(temp, "|  Score: %d  |", score));
    }
    */
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|______________|"));
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
    // needs a playerlist as input
    OLED_print(strdup("---HIGHSCORES---"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|              |"));
    OLED_print(strdup("|______________|"));
}
