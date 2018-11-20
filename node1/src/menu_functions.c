#include "parameters.h"
#include "multifunction.h"
#include "oled.h"
#include "menu.h"
#include "oled_print.h"
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include "Joy_state.h"
#include "motorbox.h"
#include "can_api.h"
#include "../../common/src/can_ids.h"

static Playerptr selectedplayer = NULL;

void mfnc_play_game() {
    //TODO run a wait loop and reset + calibrate node 2
    //TODO update score
    print_game(selectedplayer);
    can_api_value_send(CAN_ID_START_GAME, 1, 1);
    Button buttons = buttons_get_state();
    while(!buttons.left) {
        buttons = buttons_get_state();
        motorbox_send_solenoid_if_kick(buttons.right);

        Slider slider = slider_get_state();
        motorbox_send_motor_if_updated(slider.right);

        Joy_state joy_state = joy_get_state();
        int servo_val = joy_state.x / 2 + 50;
        motorbox_send_servo_if_updated(servo_val);

        _delay_ms(160); // About 10 Hz
    }
    printf("Stopping game\n\r");
    can_api_value_send(CAN_ID_STOP_GAME, 0, 1);
}

void mfnc_show_highscores() {

}

void init_current_game(Playerptr selected_player) {
    /*Current_game current_game = sram_malloc(sizeof(Current_game));
    current_game->selected_player = selected_player;
    return current_game;*/
    selectedplayer = selected_player;
}
