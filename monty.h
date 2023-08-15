#ifndef MONTY_H
#define MONTY_H

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
    void (*f)(stack_t **stack, unsigned int line_number, int value);
} instruction_t;

void push(stack_t **stack, unsigned int line_number, int value);
void pall(stack_t **stack, unsigned int line_number, int value);
void pint(stack_t **stack, unsigned int line_number, int value);
void pop(stack_t **stack, unsigned int line_number, int value);
void swap(stack_t **stack, unsigned int line_number, int value);
void add(stack_t **stack, unsigned int line_number, int value);
void nop(stack_t **stack, unsigned int line_number, int value);
int is_integer(const char *str);
void free_stack(stack_t *stack);
instruction_func find_instruction(instruction_t *instructions, char *opcode);
void handle_unknown_instruction(char *opcode, unsigned int line_number);
void exec_instr(instruction_t *instr, stack_t **stack, char *opcode, unsigned int line, int value)
int main(int argc, char *argv[])

#endif /* MONTY_H */
