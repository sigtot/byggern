#include "motor.h"
#include "../../lib/TWI_Master.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

void MOTOR_Send_Voltage(unsigned char voltage) {
    unsigned char * msg = malloc(3 * sizeof(char));
    unsigned char addr = 0x50;
    msg[0] = addr;
    msg[1] = 0;
    msg[2] = voltage;

    _delay_us(50);
    TWI_Start_Transceiver_With_Data(msg, 3);
    free(msg);
}

void MOTOR_Init() {
    TWI_Master_Initialise();
}
