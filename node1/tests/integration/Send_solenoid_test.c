

#include "parameters.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "can.h"
#include "can_ids.h"
#include "multifunction.h"
#include "motorbox.h"

int main() {
    UART_Init(MYUBRR);
	fdevopen(*UART_Transmit, *UART_Receive);

    CAN_Normal_Init();
    printf("Solenoid signal send test\n\r");

    while(1) {
        Button buttons = buttons_get_state();
        motorbox_send_solenoid_if_kick(buttons.right);
        _delay_ms(500);
    }
    return 0;
}
