#include "uart_api.h"
#include "uart.h"
#include "reference_state.h"
#include "../../common/utils/strs.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include "solenoid.h"
#include "control.h"

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
    printf("{");
    printf("\"servoPos\": %d, \"motorReference\": %d, ", Get_servo_reference(),
           Get_motor_reference());
    printf("\"KP\": %d, \"KI\": %d, \"KD\": %d", (int)(control_get_kp() * 1000),
           (int)(control_get_ki() * 1000), (int)(control_get_kd() * 1000));
    printf("}\n\r");
}

// TODO: Make not inline
static inline void handle_and_mutate() {
    char servo_str[10] = "servo";
    char motor_str[10] = "motor";
    char get_str[10] = "GET";
    char kick_str[10] = "kick";
    char K_p_str[10] = "K_p";
    char K_i_str[10] = "K_i";
    char K_d_str[10] = "K_d";
    char* servo_substr = strstr(buf, servo_str);
    char* motor_substr = strstr(buf, motor_str);
    char* get_substr = strstr(buf, get_str);
    char* kick_substr = strstr(buf, kick_str);
    char* K_p_substr = strstr(buf, K_p_str);
    char* K_i_substr = strstr(buf, K_i_str);
    char* K_d_substr = strstr(buf, K_d_str);

    if (servo_substr != NULL) {
        Set_servo_reference(
            strs_get_value_from_substr(servo_substr, strlen(servo_str)));
    }

    if (motor_substr != NULL) {
        Set_motor_reference(
            strs_get_value_from_substr(motor_substr, strlen(motor_str)));
    }

    if (get_substr != NULL) {
        respond_with_state();
    }

    if (kick_substr != NULL) {
        solenoid_send_kick();
    }

    if (K_p_substr != NULL) {
        int K_p_int = strs_get_value_from_substr(K_p_substr, strlen(K_p_str));
        control_set_kp((double)K_p_int / 1000.f);
    }

    if (K_i_substr != NULL) {
        int K_i_int = strs_get_value_from_substr(K_i_substr, strlen(K_i_str));
        control_set_ki((double)K_i_int / 1000.f);
    }

    if (K_d_substr != NULL) {
        int K_d_int = strs_get_value_from_substr(K_d_substr, strlen(K_d_str));
        control_set_kd((double)K_d_int / 1000.f);
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
