#include "monty.h"

int is_integer(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }

    int index = 0;

    if (str[index] == '+' || str[index] == '-') {
        index++;
    }

    while (str[index] != '\0') {
        if (!isdigit(str[index])) {
            return 0;
        }
        index++;
    }

    return 1;
}
