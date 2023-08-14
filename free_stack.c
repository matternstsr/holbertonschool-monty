#include "monty.h"

/**
 * free_stack - Frees all nodes in the stack.
 * @stack: Pointer to the head of the stack.
 */

void free_stack(stack_t *stack)
{
	while (stack)
	{
		stack_t *temp = stack;

		stack = stack->next;
		free(temp);
	}
}
