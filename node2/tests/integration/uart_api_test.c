#include "parameters.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "uart_api.h"
#include <avr/interrupt.h>
#include "reference_state.h"
#include "motor.h"
#include "control.h"
#include "timer.h"
#include "solenoid.h"
#include "servo.h"

static volatile int CAN_MSG_RECEIVED = 0;

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, *UART_Receive);

    printf("\n\rStarting UART API test\n\r");
    uart_api_enable();
    motor_init();
    timer_init();
    solenoid_init();
    servo_init();
    sei();
    int counter = 0;
    while (1) {
        if (_timer_flag_SHOULD_CALC_INPUT) {
            controller_calculate_and_actuate();
            _timer_flag_SHOULD_CALC_INPUT = 0;
        }
        if (!(counter % 10)) {
            solenoid_send_kick();
        } else if (!(counter % 16)) {
            servo_set_pos(Get_servo_reference());
        } else {
            _delay_ms(20);
        }
        counter++;
    }
    return 0;
}
