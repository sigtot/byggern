#include "multifunction.h"
#include "oled.h"
#include "create_menus.h"
#include "oled_print.h"
#include <stdlib.h>
#include <string.h>
#include <avr/delay.h>

#define DWN 1
#define UPP 2
#define RGT 3
#define LFT 4

uint8_t check_joystick_state() {
    _delay_ms(10);
    Joy_state joy_state = joy_get_state();
    switch (joy_state.dir) {
        case DOWN:
            return DWN;
        case UP:
            return UPP;
        case RIGHT:
            return RGT;
        case LEFT:
            return LFT;
        default:
            break;
        }
    return 0;
}

function_pointer run_test() {
    //int should_update_menu = 1;
    Nodeptr headptr = init_test();
    Nodeptr selectedptr = headptr;
    while(1) {
        print_menu();
        uint8_t state = check_joystick_state();
        if (state == UP){
            if (selectedptr->prev != NULL) {

            }
        }
    }
}

void test_function() {
    while(1) {
        _delay_ms(10);
        print_test();
        uint8_t state = check_joystick_state();
        if (state) {
            break;
        }
    }
}


void run_menu() {
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
            default:
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
    return NULL;
}
function_pointer run_highscores() {
    return NULL;
}
function_pointer run_playerlist() {
    return NULL;
}
