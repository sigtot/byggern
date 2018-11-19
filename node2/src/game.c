#include <stdio.h>
#include <util/delay.h>
#include "reference_state.h"
#include "game.h"
#include "parameters.h"
#include "timer.h"
#include "../../common/src/can_ids.h"
#include "control.h"

void game_play_round() {
    int points = 0;
    int in_game = 1;
    int ir_off = 1;
    int prev_servo = Get_servo_reference();
    while (Get_play_game_reference()) {
        if (_timer_flag_SHOULD_CALC_INPUT) {
            controller_calculate_and_actuate();
            _timer_flag_SHOULD_CALC_INPUT = 0;
        }
        int current_servo = Get_servo_reference();
        if (prev_servo != current_servo) {
            servo_set_pos(current_servo);
            prev_servo = current_servo;
        }
        if (!Ir_is_blocked()) {
            ir_off = 1;
        }
        if (Ir_is_blocked() && (ir_off == 1)) {
            ir_off = 0;
            points++;
            can_api_value_send(CAN_ID_SCORE, 1, 1);
        }
        _delay_ms(16);
    }
    printf("GGWP, you got %d points\n\r", points);
}
