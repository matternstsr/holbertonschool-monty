#include "monty.h"

/**
 * execute_instruction - Executes the appropriate instruction based on opcode.
 * @instructions: Array of instruction_t structures.
 * @stack: Double pointer to the head of the stack.
 * @opcode: Opcode of the instruction.
 * @line_number: Line number of the instruction.
 * @value: Value parameter for some instructions.
 */

void ex_in(in_t *inst, st_t *st, char *op, unsigned int line_number, int val)

{
	int i = 0;

	while (inst[i].opcode)
	{
		if (strcmp(inst[i].opcode, op) == 0)

		{
			inst[i].f(&st, line_number, val);
			return;
		}
		i++;
	}
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, op);
	free_stack(st);
	exit(EXIT_FAILURE);
}


/**
 * main - Entry point of the Monty program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings representing the command-line arguments.
 *
 * Return: EXIT_SUCCESS if successful, EXIT_FAILURE if an error occurs.
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char buffer[1024], *value_str, *opcode;
	int value;
	unsigned int line_number;
	stack_t *stack;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	stack = NULL;
	line_number = 1;
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
	while (fgets(buffer, sizeof(buffer), file))
	{
		opcode = strtok(buffer, " \t\n");
		if (opcode && opcode[0] != '#')
		{
			if (strcmp(opcode, "push") == 0)
			{
				value_str = strtok(NULL, " \t\n");
				if (value_str && is_integer(value_str))
				{
					value = atoi(value_str);
					ex_in(instructions, stack, opcode, line_number, value);
				}
				else
				{
					fprintf(stderr, "L%d: usage: push integer\n", line_number);
					free_stack(stack);
					fclose(file);
					return (EXIT_FAILURE);
				}
			}
			else
			{
				ex_in(instructions, stack, opcode, line_number, 0);
			}
		}
		line_number++;
	}

	free_stack(stack);
	fclose(file);
	return (EXIT_SUCCESS);
}
