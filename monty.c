#include "monty.h"

void execute_instruction(instruction_t *instructions, stack_t **stack, char *opcode, unsigned int line_number, int value) {
    int i = 0;
    while (instructions[i].opcode) {
        if (strcmp(instructions[i].opcode, opcode) == 0) {
            instructions[i].f(stack, line_number, value);
            return;
        }
        i++;
    }
    fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
    free_stack(*stack);
    exit(EXIT_FAILURE);
}

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
    instruction_t instructions[] = {
    {"push", push},
    {"pall", pall},
    {"pint", pint},
    {"pop", pop},
    {"swap", swap},
    {"add", add},
    {"nop", nop},
    {NULL, NULL}
};
while (fgets(buffer, sizeof(buffer), file)) {
        char *opcode = strtok(buffer, " \t\n");
        if (opcode && opcode[0] != '#') {
            char *value_str = strtok(NULL, " \t\n");
            if (value_str && is_integer(value_str)) {
                int value = atoi(value_str);
                execute_instruction(instructions, &stack, opcode, line_number, value);
            } else {
                fprintf(stderr, "L%d: usage: push integer\n", line_number);
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

