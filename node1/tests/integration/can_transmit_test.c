#include "parameters.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "can.h"
#include "can_ids.h"

int main() {
    UART_Init(MYUBRR);
	fdevopen(*UART_Transmit, *UART_Receive);

    CAN_Normal_Init();

    for (int i = 0; i < 100; i++) {
        Message message = {CAN_ID_SERVO, 1, {i}};
        CAN_Message_Send(&message);

        printf("Sent servo position %d with id %d and length %d to node2\n\r",
            message.data[0],
            message.ID,
            message.length);

        _delay_ms(1000);
    }
    return 0;
}
