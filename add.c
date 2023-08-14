#include "monty.h"

/**
 * add - Adds the top two elements of the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number of the instruction.
 * @value: Unused value parameter.
 */

void add(stack_t **stack, unsigned int line_number, int value)
{
	(void)value;
	int sum;

	if (*stack && (*stack)->next)
	{
		sum = (*stack)->n + (*stack)->next->n;
		pop(stack, line_number, value);
		(*stack)->n = sum;
	}
	else
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
}
