
#include "parameters.h"
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
#include "multifunction.h"
#include "run_oled.h"
#include "create_menus.h"
#include <stdio.h>

int main() {

    printf("OLED test\n\r");
    while (1) {
        function_pointer func = run_test();
        func();
    }
    return 0;
}
