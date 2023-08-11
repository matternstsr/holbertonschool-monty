#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "monty.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    stack_t *stack = NULL;
    char buffer[1024];
    unsigned int line_number = 1;

    while (fgets(buffer, sizeof(buffer), file)) {
        char *opcode = strtok(buffer, " \t\n");
        if (opcode && opcode[0] != '#') {
            if (strcmp(opcode, "push") == 0) {
                char *value_str = strtok(NULL, " \t\n");
                if (value_str && is_integer(value_str)) {
                    int value = atoi(value_str);
                    push(&stack, value);
                } else {
                    fprintf(stderr, "L%d: usage: push integer\n", line_number);
                    free_stack(stack);
                    fclose(file);
                    return EXIT_FAILURE;
                }
            } else if (strcmp(opcode, "pall") == 0) {
                pall(&stack, line_number);
            } else {
                fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
                free_stack(stack);
                fclose(file);
                return EXIT_FAILURE;
            }
        }
        line_number++;
    }

    free_stack(stack);
    fclose(file);
    return EXIT_SUCCESS;
}

