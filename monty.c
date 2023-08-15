#include "monty.h"

/**
 * find_instruction - Find the instruction function for the given opcode.
 * @instructions: Array of instruction_t structures.
 * @opcode: Opcode of the instruction.
 * Return: Function pointer to the instruction function, or NULL if not found.
 */
instruction_func find_instruction(instruction_t *instructions, char *opcode)
{
	for (int i = 0; instructions[i].opcode; i++)
	{
		if (strcmp(instructions[i].opcode, opcode) == 0)
			return instructions[i].f;
	}
	return NULL;
}

/**
 * handle_unknown_instruction - Handle unknown instruction error.
 * @opcode: Unknown opcode.
 * @line_number: Line number where the error occurred.
 */
void handle_unknown_instruction(char *opcode, unsigned int line_number)
{
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}

/**
 * exec_instr - Execute instruction based on opcode.
 * @instr: Array of instruction_t structs.
 * @stack: Double pointer to stack.
 * @opcode: Opcode of instruction.
 * @line: Line number.
 * @value: Value parameter for some instructions.
 */
void exec_instr(instruction_t *instr, stack_t **stack, char *opcode, unsigned int line, int value)
{
	instruction_func func = find_instruction(instr, opcode);
	if (func)
		func(stack, line, value);
	else
		handle_unknown_instruction(opcode, line);
}

 * read_and_execute_instructions - Read and execute instructions from file.
 * @file: Pointer to the input file.
 * @instructions: Array of instruction_t structures.
 */
void read_and_execute_instructions(FILE *file, instruction_t *instructions)
{
	char buffer[1024];
	unsigned int line_number = 1;
	stack_t *stack = NULL;

	while (fgets(buffer, sizeof(buffer), file))
	{
		char *opcode = strtok(buffer, " \t\n");
		if (opcode && opcode[0] != '#')
		{
			if (strcmp(opcode, "push") == 0)
			{
				char *value_str = strtok(NULL, " \t\n");
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
}

/**
 * main - Entry point of Monty program.
 * @argc: Number of command-line arguments.
 * @argv: Array of strings representing arguments.
 *
 * Return: EXIT_SUCCESS if successful, EXIT_FAILURE if error occurs.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	instruction_t instr[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{NULL, NULL}
	};

	read_and_execute_instructions(file, instr);

	fclose(file);
	return (EXIT_SUCCESS);
}
