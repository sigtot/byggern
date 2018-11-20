
#include "reference_state.h"
#include "parameters.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "motor.h"
#include "control.h"
#include "solenoid.h"
#include "timer.h"
#include "can_api.h"
#include "servo.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);
    solenoid_init();
    ir_init();
    motor_init();
    can_api_init();
    CAN_Normal_Init();
    servo_init();
    timer_init();
    sei();

    while (1) {
        if (Get_play_game_reference()) {
            game_play_round();
        }
    }

    return 0;
}
