#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

#define SUCCESS 0
#define TRUE 1
#define CREATE_FAIL -1
#define INPUT_FAIL -1
#define MAX 100
#define ITERATIONS (long int) 1

stack_type *allocate_stack(void)
{
    stack_type *stack = (stack_type*)malloc(sizeof (stack_type));
    stack->head = NULL;

    return stack;
}

stack_pointer_type *allocate_pointer_stack(void)
{
    stack_pointer_type *stack = (stack_pointer_type*)malloc(sizeof (stack_pointer_type));
    stack->head = NULL;

    return stack;
}

void push_stack(stack_type *stack, char symbol)
{
    element_t *element_of_stack = (element_t*)malloc(sizeof (element_t));
    element_of_stack->next = stack->head;
    element_of_stack->symb = symbol;
    stack->head = element_of_stack;
    stack->size++;
}

void push_pointer_stack(stack_pointer_type *stack, element_t *element_of_stack)
{
    element_pointer_t *cur_head = (element_pointer_t*)malloc(sizeof (element_pointer_t));
    cur_head->next = stack->head;
    cur_head->pointer = element_of_stack;
    stack->head = cur_head;
}

char pop_stack(stack_type *stack)
{
    element_t *pointer = stack->head;
    char symb;

    stack->head = pointer->next;
    symb = pointer->symb;
    free(pointer);
    stack->size--;

    return symb;
}

void output_stack(stack_type *stack)
{
    element_t *pointer = stack->head;

    printf("Количество элементов стэка:%d\n", stack->size);
    printf("Стэк хранящийся в виде односвязного списка.\n");
    printf("Элементы стэка:\n");
    while (pointer != NULL)
    {
        printf("Значение элемента:%c и его адрес %p\n", pointer->symb, pointer);
        pointer = pointer->next;
    }
}

void output_pointer_stack(stack_pointer_type *stack)
{
    element_pointer_t *pointer = stack->head;

    printf("Освобожденные элементы:\n");
    while (pointer != NULL)
    {
        printf("%p\n", pointer->pointer);
        pointer = pointer->next;
    }
}

void free_stack(stack_type *stack)
{
    element_t *pointer = stack->head, *prev_pointer = stack->head;

    if (stack->head == NULL)
        return;
    while (stack->head->next != NULL)
    {
        while (pointer->next != NULL)
        {
            prev_pointer = pointer;
            pointer = pointer->next;
        }

        free(pointer);
        prev_pointer->next = NULL;
        pointer = stack->head;
        prev_pointer = stack->head;
    }

    stack->head = NULL;
    free(stack);
}

void free_pointer_stack(stack_pointer_type *stack)
{
    element_pointer_t *pointer = stack->head, *prev_pointer = stack->head;

    if (stack->head == NULL)
        return;
    while (stack->head->next != NULL)
    {
        while (pointer->next != NULL)
        {
            prev_pointer = pointer;
            pointer = pointer->next;
        }

        free(pointer);
        prev_pointer->next = NULL;
        pointer = stack->head;
        prev_pointer = stack->head;
    }

    stack->head = NULL;
    free(stack);
}

int check_for_palindrom(stack_type *main_stack, stack_type *second_stack, stack_pointer_type *pointer_stack)
{
    char symb, cur_symb;

    main_stack->size = 0;
    while (1)
    {
        push_pointer_stack(pointer_stack, main_stack->head);
        symb = pop_stack(main_stack);
        if (symb >= 65 && symb <= 90)
            symb += 32;
        if (main_stack->head == NULL)
        {
            return 1;
        }
        while (main_stack->head->next != NULL)
        {
            cur_symb = pop_stack(main_stack);
            push_stack(second_stack, cur_symb);
        }

        push_pointer_stack(pointer_stack, main_stack->head);
        cur_symb = pop_stack(main_stack);
        if (cur_symb >= 65 && cur_symb <= 90)
            cur_symb += 32;
        if (symb != cur_symb)
        {
            while (second_stack->head != NULL)
            {
                cur_symb = pop_stack(second_stack);
                push_stack(main_stack, cur_symb);
            }
            return 0;
        }
        if (symb == cur_symb)
        {
            if (second_stack->head == NULL)
            {
                return 1;
            }
            while (second_stack->head != NULL)
            {
                cur_symb = pop_stack(second_stack);
                push_stack(main_stack, cur_symb);
            }
        }
    }
}

void check_pointer_stack(stack_type *main_stack, stack_pointer_type *pointer_stack)
{
    element_pointer_t *pointer_for_free = pointer_stack->head; //*prev_pointer = pointer_stack->head;
    element_t *pointer = main_stack->head;
    //int flag;

    while (pointer_for_free->pointer == pointer && pointer_stack->head != NULL)
    {
        pointer_stack->head = pointer_for_free->next;
        pointer_for_free = pointer_stack->head;
    }

    /*pointer_for_free = prev_pointer->next;
    while (pointer_for_free->pointer != NULL && prev_pointer != NULL)
    {
        flag = 0;
        if (pointer_for_free->pointer == pointer)
        {
            prev_pointer->next = pointer_for_free->next;
            flag = 1;
        }
        if (!flag)
            prev_pointer = prev_pointer->next;
        pointer_for_free = prev_pointer->next;
    }*/
}
