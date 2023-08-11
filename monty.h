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

void push(stack_t **stack, int value);
void pall(stack_t **stack, unsigned int line_number);
int is_integer(const char *str);
void free_stack(stack_t *stack);

#endif /* MONTY_H */

