#include "monty.h"


/**
 * pint - Prints the top element of the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number of the instruction.
 * @value: Unused value parameter.
 */
void pint(stack_t **stack, unsigned int line_number, int value) {
    (void)value;
    (void)line_number;
    if (*stack) {
        printf("%d\n", (*stack)->n);
    } else {
        fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
        free_stack(*stack);
        exit(EXIT_FAILURE);
    }
}
