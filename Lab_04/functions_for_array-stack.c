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

void push_stack_array(char *stack, int size, char symb)
{
    char *pointer = stack + size;

    *pointer = symb;
}

char pop_stack_array(char *stack, int size)
{
    char r_symb = *(stack + size - 1);

    return r_symb;
}

void output_stack_array(char *stack, int size)
{
    char *pointer = stack + size - 1;
    int i = size;

    printf("Стэк хранящайся в виде массива.\n");
    printf("Элементы стэка:\n");
    while (i > 0)
    {
        printf("Значение элемента:%c\n", *pointer);
        pointer--;
        i--;
    }
}

int check_for_palindrom_array(char *main_stack, int size)
{
    char *second_stack = (char*)malloc(sizeof(char) * (size - 2)), *pointer;
    char symb, cur_symb;
    int second_size;

    while (1)
    {
        second_size = 0;

        symb = pop_stack_array(main_stack, size);
        pointer = main_stack;
        size--;

        if (symb >= 65 && symb <= 90)
            symb += 32;
        if (size == 0)
        {
            free(second_stack);
            return 1;
        }
        while (size > 0)
        {
            cur_symb = pop_stack_array(main_stack, size);
            size--;
            push_stack_array(second_stack, second_size, cur_symb);
            second_size++;
        }

        cur_symb = pop_stack_array(main_stack, size);
        size--;
        if (cur_symb >= 65 && cur_symb <= 90)
            cur_symb += 32;
        if (symb != cur_symb)
        {
            while (second_size > 0)
            {
                cur_symb = pop_stack_array(second_stack, second_size);
                second_size--;
                push_stack_array(main_stack, size, cur_symb);
                size++;
            }
            free(second_stack);
            return size;
        }
        if (symb == cur_symb)
        {
            if (second_size == 0)
            {
                free(second_stack);
                return 1;
            }
            while (second_size > 0)
            {
                cur_symb = pop_stack_array(second_stack, second_size);
                second_size--;
                push_stack_array(main_stack, size, cur_symb);
                size++;
            }
        }
    }
}


