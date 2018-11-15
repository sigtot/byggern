
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
    printf("Right slider CAN send test\n\r");
    while(1) {
        Slider slider = slider_get_state();
        motorbox_send_motor_if_updated(slider.right);
        _delay_ms(100);
    }
    return 0;
}
