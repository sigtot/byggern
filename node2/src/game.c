#include "game.h"
#include "parameters.h"
#include <avr/delay.h>
#include "reference_state.h"

void game_play_round() {
    int points = 0;
    int in_game = 1;
    while(in_game) {
        points++;
        if (Ir_is_blocked()) {
            in_game = 0;
        }
        _delay_ms(16);
    }
    printf("GGWP, you got %d points\n\r", points);
}
