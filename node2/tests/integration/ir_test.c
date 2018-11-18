#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "reference_state.h"

#include "ir.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);

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
        int new = !Ir_is_blocked();
        if (ir_light_received != new) {
            ir_light_received = new;
            printf("%s\n\r", ir_light_received ? "RECEIVING IR LIGHT"
                                               : "NOT RECEIVING IR LIGHT");
        }
    }
    return 0;
}
