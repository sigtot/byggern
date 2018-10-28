#ifndef F_CPU
#define F_CPU 16000000
#endif
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include "uart.h"

int main() {
    // Main
}
