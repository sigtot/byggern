#include <stdio.h>
#include <util/delay.h>
#include "reference_state.h"
#include "game.h"
#include "parameters.h"
#include "timer.h"
#include "../../common/src/can_ids.h"
#include "control.h"

static uint8_t time_is_up = 0;

void game_play_round() {
    int fail = 0;
    int in_game = 1;
    int ir_off = 1;
    while (Get_play_game_reference()) {
        if (_timer_flag_SHOULD_CALC_INPUT) {
            controller_calculate_and_actuate();
            _timer_flag_SHOULD_CALC_INPUT = 0;
        }
        if (!Ir_is_blocked()) {
            ir_off = 1;
        }
        if (Ir_is_blocked() && (ir_off == 1)) {
            ir_off = 0;
            fail++;
        }
        if (fail && time_is_up) {
            fail = 0;
            break;
        }
        _delay_ms(16);
    }
}

void set_time_is_up() {
    time_is_up = 1;
}
