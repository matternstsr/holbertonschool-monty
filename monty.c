#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct stack_s {
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

typedef struct instruction_s {
    char *opcode;
    void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void push(stack_t **stack, int value);
void pall(stack_t **stack, unsigned int line_number);
int is_integer(const char *str);
void free_stack(stack_t *stack);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    stack_t *stack = NULL;
    char buffer[1024];
    unsigned int line_number = 1;

    while (fgets(buffer, sizeof(buffer), file))
    {
        char *opcode = strtok(buffer, " \t\n");
        if (opcode && opcode[0] != '#')
	{ // Ignore comment lines
        if (strcmp(opcode, "push") == 0)
	{
		char *value_str = strtok(NULL, " \t\n");
		if (value_str && is_integer(value_str))
		{
			int value = atoi(value_str);
			push(&stack, value);  // Pass the value to the push function
		}
		else
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			free_stack(stack);
			fclose(file);
			return EXIT_FAILURE;
		}
	}
    
	} else if (strcmp(opcode, "pall") == 0) {
                pall(&stack, line_number);
            } else {
                fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
                free_stack(stack);
                fclose(file);
                return EXIT_FAILURE;
            }
        }
        line_number++;
    }

    free_stack(stack);
    fclose(file);
    return EXIT_SUCCESS;
}
