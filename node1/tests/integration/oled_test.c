#include "parameters.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "multifunction.h"
#include "run_oled.h"
#include "create_menus.h"
#include <stdio.h>
#include "oled_print.h"
#include "run_oled.h"
#include "oled.h"

int main() {
    UART_Init(MYUBRR);
    fdevopen(*UART_Transmit, *UART_Receive);
    printf("Testing OLED. You should see \"Hello world!\" print.\n\r");
    oled_init();
    char str[16] = "Hello world!";
    OLED_clear();
    OLED_print(str);
    while (1)
        ;
    return 0;
}
