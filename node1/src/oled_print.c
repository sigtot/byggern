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
    _delay_ms(200);
}

void print_game(Playerptr playerptr) {
    OLED_clear();
    OLED_print_page(strdup("-GAME IS ACTIVE-"), 0);
    OLED_print_page(strdup("|              |"), 1);
    OLED_print_page(strdup("|  Good luck,  |"), 2);
    OLED_print_page(strdup("|              |"), 3);
    OLED_print_page(strdup("|              |"), 4);
    OLED_print_page(strdup("|              |"), 5);
    OLED_print_page(strdup("|              |"), 6);
    OLED_print_page(strdup("|______________|"), 7);
    OLED_pos(3, (128 - strlen(playerptr->name) * 8) / 2);
    OLED_print(playerptr->name);
    // just checking if it appears as should
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
    OLED_clear();

    OLED_print_page(strdup("---HIGHSCORES-- "), 0);
    uint8_t i = 1;
    Playerptr selectedplayer = playerptr;
    while ((playerptr != NULL) && (i < 8)) {
        OLED_print_page(playerptr->name, i);
        char buf[10];
        itoa(playerptr->score, buf, 10);
        OLED_pos(i, 128 - strlen(buf) * 8);
        OLED_print(buf);
        i++;
        playerptr = playerptr->next;
    }
}
