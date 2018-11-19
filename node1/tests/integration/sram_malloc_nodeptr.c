#include "parameters.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "sram.h"
#include "uart.h"
#include "Joy_state.h"
#include "multifunction.h"
#include "oled.h"


#define PAGE_LENGTH 14
#define PAGE_BUFFER_SIZE (PAGE_LENGTH + 1)

typedef void (*function_pointer)();
typedef struct node* Nodeptr;
typedef struct node {
        char* text;
        Nodeptr next;
        Nodeptr prev;
        Nodeptr parent;
        Nodeptr child;
        function_pointer func;
    } Node;

int test_func() {
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
    child->func = test_func;

    Nodeptr thirdptr = init_node(secondptr, NULL, "Third item");
    secondptr->next = thirdptr;

    printf("Thirdptr->next: %02x\n\r", thirdptr->next);
    printf("headptr->prev: %02x\n\r", headptr->prev);
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
    fdevopen(*UART_Transmit, NULL);
    oled_init();
    printf("Initializing SRAM...\n\r");
    sram_init();
    printf("SRAM successfully initialized. Testing sram_sram_malloc nodepointer\n\r");
    volatile char* sram = (char*)SRAM_ADDRESS;

    for (int i = 0; i < 164; i++) {
        printf("%2x ", sram[i]);
        if (!((i+1)%16)){
            printf("\n\r");
        }
    }

    Nodeptr selectedptr = init_test_menu();
    print_menu(selectedptr);



    for (int i = 0; i < 164; i++) {
        printf("%02x ", sram[i]);
        if (!((i+1)%16)){
            printf("\n\r");
        }
    }


    printf("\n\rSRAM_sram_sram_malloc nodepointer test finished.\n\r");
    while(1);
    return 0;
}
