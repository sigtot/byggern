#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "can.h"
#include "can_ids.h"
#include "can_api.h"
#include "parameters.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, *UART_Receive);

    can_api_init();

    for (int i = 0; i < 100; i++) {
        can_api_value_send(CAN_ID_SCORE, 4, 1);

        printf("Sent score 4 with id CAN_ID_SCORE and length 1 to node2\n\r");

        _delay_ms(1000);
    }
    return 0;
}
