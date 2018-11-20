#include "parameters.h"
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "Joy_state.h"
#include "multifunction.h"
#include "menu.h"
#include "sram.h"
#include "can_api.h"
#include "timer.h"


int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, *UART_Receive);
    printf("Node 1 main\n\r");

    timer_init();
    can_api_init();
    menu_init();
    sram_init();

    Playerptr selectedplayer = init_players();
    init_current_game(selectedplayer);
    Nodeptr menu_selectedptr = init_create_main_menu();
    print_menu(menu_selectedptr);
    while (1) {
        _delay_ms(10);
        Joy_state joy_state = joy_get_state();
        if ((joy_state.dir == RIGHT) && (menu_selectedptr->func != NULL)) {
            //printf("ptr before: %02x\n\r", menu_selectedptr->prev);
            menu_selectedptr->func(menu_selectedptr);
            //printf("ptr after: %02x\n\r", menu_selectedptr->prev);
            print_menu(menu_selectedptr);
        }
        if (joy_state.dir != NEUTRAL) {
            Nodeptr prevptr = menu_selectedptr;
            menu_selectedptr = update_menu(menu_selectedptr, joy_state.dir);
            int menu_updated = menu_selectedptr != prevptr;
            if (menu_updated) {
                print_menu(menu_selectedptr);
                _delay_ms(200);
            }
        }
    }
}
