#include "parameters.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "can_api.h"
#include <avr/interrupt.h>
#include "reference_state.h"

static volatile int CAN_MSG_RECEIVED = 0;

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, *UART_Receive);

    printf("\n\rStarting CAN receive test with INT\n\r");

    can_api_init();
    EICRA &= ~(1 << ISC30); // Interrupt on falling edge
  	EICRA |= (1 << ISC31); // Interrupt on falling edge
  	EIMSK |= (1 << INT3); // Enable interrupt on INT3

    sei();
    while(1) {
        printf("Servo position: %d\n\r", Get_servo_reference());
        _delay_ms(200);
    }
    return 0;
}
