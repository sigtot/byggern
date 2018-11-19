#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "reference_state.h"
#include "parameters.h"
#include "ir.h"
#include "can.h"
#include "can_ids.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);
    can_api_init();

    printf(
        "Test instruction: Hold the IR emmitter up to the photo diode. The "
        "test will alert you when the state changes.\n\r");
    ir_init();
    sei();

    _delay_ms(20);
    int ir_light_received = !Ir_is_blocked();
    printf("%s\n\r",
           ir_light_received ? "RECEIVING IR LIGHT" : "NOT RECEIVING IR LIGHT");
    while (1) {
        if (Ir_is_blocked()) {
            can_api_value_send(CAN_ID_SCORE, 1, 1);
        }

        int new = !Ir_is_blocked();
        if (ir_light_received != new) {
            ir_light_received = new;
            printf("%s\n\r", ir_light_received ? "RECEIVING IR LIGHT"
                                               : "NOT RECEIVING IR LIGHT");
        }
        _delay_ms(1000);
    }
    return 0;
}
