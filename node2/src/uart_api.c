#include "uart_api.h"
#include "uart.h"
#include "reference_state.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 100

// TODO: Make static
char buf[BUF_SIZE];
int cursor = 0;
volatile int RECEIVING_BYTE = 0;
static volatile int API_ENABLED = 0;

void uart_api_enable() {
    UART_INT_Enable();
    API_ENABLED = 1;
}

void respond_with_state() {
    printf("{\"servoPos\": %d, \"motorReference\": %d}\n\r",
           Get_servo_reference(), Get_motor_reference());
}

// TODO: Make not inline
static inline void handle_and_mutate() {
    char servo_str[10] = "servo";
    char motor_str[10] = "motor";
    char get_str[10] = "GET";
    char* servo_substr = strstr(buf, servo_str);
    char* motor_substr = strstr(buf, motor_str);
    char* get_substr = strstr(buf, get_str);

    if (servo_substr != NULL) {
        Set_servo_reference(
            get_value_from_substr(servo_substr, strlen(servo_str)));
    }

    if (motor_substr != NULL) {
        Set_motor_reference(
            get_value_from_substr(motor_substr, strlen(motor_str)));
    }

    if (get_substr != NULL) {
        respond_with_state();
    }
}

ISR(USART0_RX_vect) {
    if (!API_ENABLED) {
        return;
    }
    while (RECEIVING_BYTE)
        ;  // Wait for any previous receive to finish
    RECEIVING_BYTE = 1;
    // Read UDR register to reset flag
    unsigned char data = UDR0;
    // Check for error
    if ((UCSR0A & ((1 << FE0) | (1 << DOR0) | (1 << UPE0))) == 0) {
        // New frame incoming
        if (data == '{') {
            cursor = 0;
        }

        buf[cursor] = data;

        // Frame finished, mutate state
        if (data == '}') {
            buf[cursor + 1] = '\0';  // End the string so string functions work
            handle_and_mutate();
            cursor = 0;
        } else if (cursor < BUF_SIZE - 2) {
            cursor++;
        } else {
            cursor = 0;  // Wrap around on buffer overflow
        }
    }
    RECEIVING_BYTE = 0;
}

int get_value_from_substr(char* substr, int key_length) {
    char valid_chars[15] = "0123456789";
    char* number_substr_start = substr + key_length + 1;
    char number_substr[10] = "";
    strncpy(number_substr, number_substr_start,
            strspn(number_substr_start, valid_chars));
    return atoi(number_substr);
}
