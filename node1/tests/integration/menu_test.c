#include "parameters.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "multifunction.h"
#include "run_oled.h"
#include "menu.h"
#include <stdio.h>
#include "multifunction.h"
#include "oled_print.h"
#include "run_oled.h"
#include "oled.h"

int test_function() {
    print_test();
    _delay_ms(500);
    while (joy_get_state().dir == NEUTRAL)
        ;
    return 0;
}

Nodeptr init_test_menu() {
    Nodeptr headptr = init_node(NULL, NULL, "Node 1");

    Nodeptr secondptr = init_node(headptr, NULL, "To submenu");
    headptr->next = secondptr;

    Nodeptr child = init_node(NULL, secondptr, "Test func");
    secondptr->child = child;

    child->func = test_function;

    Nodeptr thirdptr = init_node(secondptr, NULL, "123456789123456");
    secondptr->next = thirdptr;

    Nodeptr fourthptr =
        init_node(thirdptr, NULL, "Long string which will be truncated");
    thirdptr->next = fourthptr;

    return headptr;
}

void print_test() {
    char* str = strdup("-TEST FUNCTION-");
    OLED_clear();
    OLED_print(str);
    free(str);
}

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, *UART_Receive);
    printf("Menu test\n\r");
    oled_init();
    sram_init();
    Nodeptr selectedptr = init_test_menu();
    print_menu(selectedptr);
    while (1) {
        Joy_state joy_state = joy_get_state();
        if ((joy_state.dir == RIGHT) && (selectedptr->func != NULL)) {
            selectedptr->func();
            _delay_ms(200);
        }
        Nodeptr prevptr = selectedptr;
        selectedptr = update_menu(selectedptr, joy_state);
        if (selectedptr != prevptr) {
            print_menu(selectedptr);
            _delay_ms(200);
        }
    }
    return 0;
}
