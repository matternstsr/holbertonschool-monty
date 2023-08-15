#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define the struct for the stack */
typedef struct stack_s
{
    int n;
    struct stack_s *prev;
} stack_t;

/* Define the struct for Monty instructions */
typedef struct instruction_s
{
    char *opcode;
    void (*func)(stack_t **stack, unsigned int line_number, int value);
} instruction_t;

/* Function prototypes */
void exec_instr(instruction_t *instr, stack_t **stack, char *opcode, unsigned int line, int value);
void free_stack(stack_t *stack);
int is_integer(const char *str);
void read_and_execute_instructions(FILE *file, instruction_t *instructions, stack_t **stack);
instruction_func find_instruction(instruction_t *instructions, char *opcode);

/* Function prototypes for Monty instructions */
void push(stack_t **stack, unsigned int line_number, int value);
void pall(stack_t **stack, unsigned int line_number, int value);
void pint(stack_t **stack, unsigned int line_number, int value);
void pop(stack_t **stack, unsigned int line_number, int value);
void swap(stack_t **stack, unsigned int line_number, int value);
void add(stack_t **stack, unsigned int line_number, int value);
void nop(stack_t **stack, unsigned int line_number, int value);

/* Other macros and constants... */

#endif /* MONTY_H */

