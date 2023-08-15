#include "monty.h"

/**
 * execute_instruction - Executes the appropriate instruction based on opcode.
 * @instructions: Array of instruction_t structures.
 * @stack: Double pointer to the head of the stack.
 * @opcode: Opcode of the instruction.
 * @line_number: Line number of the instruction.
 * @value: Value parameter for some instructions.
 */

#include "monty.h"

void execute_instruction(instruction_t *instructions, stack_t **stack,
						 char *opcode, unsigned int line_number, int value)
{
	int i = 0;

	while (instructions[i].opcode)
	{
		if (strcmp(instructions[i].opcode, opcode) == 0)
		{
			instructions[i].f(stack, line_number, value);
			return;
		}
		i++;
	}
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
	free_stack(*stack);
	exit(EXIT_FAILURE);
}

/**
 * main - Entry point of the Monty program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings representing the command-line arguments.
 * Return: EXIT_SUCCESS if successful, EXIT_FAILURE if an error occurs.
 */

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	process_file(argv[1]);

	return (0);
}


/**
 * process_file - Process a Monty bytecode file and execute instructions.
 * @filename: The name of the Monty bytecode file to be processed.
 */

void process_file(const char *filename)
{
	FILE *file = fopen(filename, "r");

	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	stack_t *stack = NULL;
	char buffer[1024], char *opcode, char *value_str;
	unsigned int line_number = 1;

	instruction_t instructions[] = {
    {"push", push}, {"pall", pall}, {"pint", pint}, {"pop", pop},
    {"swap", swap}, {"add", add}, {"nop", nop}, {NULL, NULL}
};
	while (fgets(buffer, sizeof(buffer), file))
	{
		*opcode = strtok(buffer, " \t\n");
		if (opcode && opcode[0] != '#')
	{
			if (strcmp(opcode, "push") == 0)
		{
				*value_str = strtok(NULL, " \t\n");
				if (value_str && is_integer(value_str))
		{
					int value = atoi(value_str);

					execute_instruction(instructions, &stack, opcode, line_number, value);
				}
		else
		{
					fprintf(stderr, "L%d: usage: push integer\n", line_number);
					free_stack(stack);
					fclose(file);
					exit(EXIT_FAILURE);
				}
			}
		else
		{
				execute_instruction(instructions, &stack, opcode, line_number, 0);
			}
		}
		line_number++;
	}
	free_stack(stack);
	fclose(file);
	exit(EXIT_SUCCESS);
}
