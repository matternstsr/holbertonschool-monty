#include "monty.h"




void swap(stack_t **stack, unsigned int line_number, int value) {
    (void)value;
    (void)line_number;
    if (*stack && (*stack)->next) {
        int temp = (*stack)->n;
        (*stack)->n = (*stack)->next->n;
        (*stack)->next->n = temp;
    } else {
        fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
        free_stack(*stack);
        exit(EXIT_FAILURE);
    }
}

