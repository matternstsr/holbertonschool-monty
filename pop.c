#include "monty.h"




void pop(stack_t **stack, unsigned int line_number, int value) {
    (void)value;
    (void)line_number;
    if (*stack) {
        stack_t *temp = *stack;
        *stack = (*stack)->next;
        if (*stack) {
            (*stack)->prev = NULL;
        }
        free(temp);
    } else {
        fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
        free_stack(*stack);
        exit(EXIT_FAILURE);
    }
}
