#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#endif // HEADER_H

typedef struct element_s
{
    struct element_s *next;
    char symb;
} element_t;

typedef struct element_pointer_s
{
    element_t *pointer;
    struct element_pointer_s *next;
} element_pointer_t;

typedef struct stack_s
{
    element_t *head;
    int size;
} stack_type;

typedef struct stack_pointer_s
{
    element_pointer_t *head;
} stack_pointer_type;

stack_type *allocate_stack(void);
stack_pointer_type *allocate_pointer_stack(void);
void push_stack(stack_type *stack, char symbol);
void push_stack_array(char *stack, int size, char symb);
void push_pointer_stack(stack_pointer_type *stack, element_t *element_of_stack);
char pop_stack(stack_type *stack);
char pop_stack_array(char *stack, int size);
void output_stack(stack_type *stack);
void output_pointer_stack(stack_pointer_type *stack);
void output_stack_array(char *stack, int size);
void free_stack(stack_type *stack);
void free_pointer_stack(stack_pointer_type *stack);
int check_for_palindrom(stack_type *main_stack, stack_type *second_stack, stack_pointer_type *pointer_stack);
int check_for_palindrom_array(char *main_stack, int size);
void check_pointer_stack(stack_type *main_stack, stack_pointer_type *pointer_stack);

