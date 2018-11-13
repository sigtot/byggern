#include "uart_api.h"
#include "uart.h"
#include "state.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 100

char buf[BUF_SIZE];
int cursor = 0;
volatile int RECEIVING_BYTE = 0;

static inline void handle_and_mutate() {
    char servo_str[10] = "servo";
    char motor_str[10] = "motor";
    char * servo_substr = strstr(buf, servo_str);
    char * motor_substr = strstr(buf, motor_str);

    if (servo_substr != NULL) {
        Set_servo_pos(get_value_from_substr(servo_substr, strlen(servo_str)));
    }
    if (motor_substr != NULL) {
        Set_motor_reference(get_value_from_substr(motor_substr, strlen(motor_str)));
    }
}

ISR(USART0_RX_vect)
{
	while(RECEIVING_BYTE); // Wait for any previous receive to finish
	RECEIVING_BYTE = 1;
	// Read UDR register to reset flag
	unsigned char data = UDR0;
	// Check for error
	if((UCSR0A & ((1 << FE0) | (1 << DOR0) | (1 << UPE0))) == 0)
	{
		// New frame incoming
		if(data == '{') {
            cursor = 0;
		}

        buf[cursor] = data;

        // Frame finished, mutate state
        if(data == '}') {
            buf[cursor + 1] = '\0'; // End the string so string functions work
            printf("Received: %s\n\r", buf);
            handle_and_mutate();
            printf("New servo val: %d\n\r", Get_servo_pos());
            printf("New motor reference: %d\n\r", Get_motor_reference());
            cursor = 0;
        } else if (cursor < BUF_SIZE - 2) {
            cursor++;
        } else {
            cursor = 0; // Wrap around on buffer overflow
        }
	}
	RECEIVING_BYTE = 0;
}

int get_value_from_substr(char * substr, int key_length) {
    char valid_chars[15] = "0123456789";
    char * number_substr_start = substr + key_length + 1;
    char number_substr[10] = "";
    strncpy(number_substr, number_substr_start, strspn(number_substr_start, valid_chars));
    return atoi(number_substr);
}
