#include "parameters.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "motor.h"
#include "inttypes.h"

#include "ir.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, NULL);

    printf(
        "Test instruction: Wait for the motor to calibrate, then move it "
        "around and watch the encoder value change.\n\r");
    motor_init();
    _delay_ms(20);
    printf("DDRK: %2x, DDRH: %2x, PORTH: %2x", DDRK, DDRH, PORTH);
    _delay_ms(1000);
    while (1) {
        int16_t val = motor_read_encoder();
        printf("Encoder value: %" PRId16 " (%d)\n\r", val, val);
    }
    return 0;
}
