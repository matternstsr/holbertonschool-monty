#include "monty.h"

/**
 * pall - Prints all elements in the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number of the instruction.
 * @value: Unused value parameter.
 */
void pall(stack_t **stack, unsigned int line_number, int value) {
    (void)value;
    (void)line_number;
    stack_t *current = *stack;
    while (current) {
        printf("%d\n", current->n);
        current = current->next;
    }
}
