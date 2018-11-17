#include "menu.h"
#include "multifunction.h"
#include "oled.h"
#include <stdlib.h>
#include <string.h>
#include <avr/delay.h>

#define down 1
#define up 2
#define right 3
#define left 4

uint8_t check_joystick_state() {
    _delay_ms(10);
    switch (joy_state.dir) {
        case DOWN:
            return down;
        case UP:
            return up;
        case RIGHT:
            return right;
        case LEFT:
            return left;
        }
    return 0;
}

function_pointer run_test() {
    int should_update_menu = 1;
    Nodeptr headptr = init_menu();
    Nodeptr selectedptr = headptr;
    
}


function_pointer run_menu() {
    int should_update_menu = 1;
    Nodeptr headptr = init_menu();
    Nodeptr selectedptr = headptr;
    Playerptr playerptr = init_players();
    Playerptr selected_player = playerptr;
    while (1) {
        _delay_ms(10);
        Joy_state joy_state = joy_get_state();
        motorbox_send_servo_if_updated(Joy_state_get_servo_value(joy_state));
        Slider slider = slider_get_state();
        motorbox_send_motor_if_updated(slider.right);
        Button buttons = buttons_get_state();
        motorbox_send_solenoid_if_kick(buttons.right);
        switch (joy_state.dir) {
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
            //_delay_ms(300); // Wait a little after each interraction with GUI
            should_update_menu = 0;
        }
    }
}

function_pointer run_game() {

}
function_pointer run_highscores();
function_pointer run_playerlist();
