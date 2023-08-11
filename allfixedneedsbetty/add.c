#include "monty.h"



void add(stack_t **stack, unsigned int line_number, int value) {
    (void)value;
    if (*stack && (*stack)->next) {
        int sum = (*stack)->n + (*stack)->next->n;
        pop(stack, line_number, value);
        (*stack)->n = sum;
    } else {
        fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
        free_stack(*stack);
        exit(EXIT_FAILURE);
    }
}
