#include "strs.h"

int strs_get_value_from_substr(char* substr, int key_length) {
    char valid_chars[15] = "0123456789";
    char* number_substr_start = substr + key_length + 1;
    char number_substr[10] = "";
    strncpy(number_substr, number_substr_start,
            strspn(number_substr_start, valid_chars));
    return atoi(number_substr);
}
