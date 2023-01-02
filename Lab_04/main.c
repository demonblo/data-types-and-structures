#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

#define SUCCESS 0
#define TRUE 1
#define CREATE_FAIL -1
#define INPUT_FAIL -1

#define MAX 300
#define ITERATIONS 1000000

int main()
{
    stack_type *main_stack, *second_stack, *third_stack;
    stack_pointer_type *pointer_stack;
    char symb, *char_stack_b = (char*)malloc(sizeof(char) * MAX);
    char flag;
    int check, size_of_stack = 0;

    main_stack = allocate_stack();
    second_stack = allocate_stack();
    pointer_stack = allocate_pointer_stack();
    while (1)
    {
        printf("\n");
        printf("\n");
        printf("Main menu\n");
        printf("\n");
        printf("\n");
        printf("Выберите пункт меню:\n");
        printf("1)Добавить элемент в стэк.\n");
        printf("2)Удалить элемент из стэка.\n");
        printf("3)Вывести состояние стэка.\n");
        printf("4)Сразу ввести строку.\n");
        printf("5)Проверить, является ли строка, хранящаяся в стэке, палиндромом.\n");
        printf("6)Сравнить стэк реализованный списком и массивом.\n");
        printf("0)Выход.\n");
        printf("Примечание: Максимальное кол-во элментов стэка - 300!\n");
        printf("\n");
        if (scanf("%c", &flag) != 1)
        {
            free(char_stack_b);
            free_stack(main_stack);
            free_stack(second_stack);
            printf("Некорректный ввод!\n");
            return INPUT_FAIL;
        }
        if (flag == '\n')
        {
            free(char_stack_b);
            free_stack(main_stack);
            free_stack(second_stack);
            free_pointer_stack(pointer_stack);
            printf("Пустой ввод!\n");
                return INPUT_FAIL;
        }
        else if (flag == '1')
        {
            getchar();
            if (main_stack->size == MAX)
            {
                printf("Достигнут максимум элементов!\n");
            }
            else
            {
                printf("Введите элемент:");
                if (scanf("%c", &symb) != 1)
                {
                    free(char_stack_b);
                    free_stack(main_stack);
                    free_stack(second_stack);
                    free_pointer_stack(pointer_stack);
                    printf("Некорректный ввод!\n");
                    return INPUT_FAIL;
                }
                if (symb == '\n' || symb == ' ')
                {
                    printf("Пустой ввод!\n");
                    free(char_stack_b);
                    free_stack(main_stack);
                    free_stack(second_stack);
                    free_pointer_stack(pointer_stack);
                    return INPUT_FAIL;
                }
                push_stack(main_stack, symb);
                if (pointer_stack->head != NULL)
                    check_pointer_stack(main_stack, pointer_stack);
                push_stack_array(char_stack_b, size_of_stack, symb);
                size_of_stack++;
                while (getchar() != '\n');
            }
        }
        else if (flag == '2')
        {
            getchar();
            if (main_stack->head != NULL)
            {
                push_pointer_stack(pointer_stack, main_stack->head);
                pop_stack(main_stack);
                pop_stack_array(char_stack_b, size_of_stack);
                size_of_stack--;
            }
            else
                printf("Стэк пуст!\n");
        }
        else if (flag == '3')
        {
            getchar();
            if (main_stack->head != NULL)
            {
                output_stack(main_stack);
                output_stack_array(char_stack_b, size_of_stack);
                if (pointer_stack->head == NULL)
                    printf("Ни один элемент не был 'освобождён'\n");
                else
                    output_pointer_stack(pointer_stack);
            }
            else
            {
                printf("Стэк пуст!\n");
                if (pointer_stack->head == NULL)
                    printf("Ни один элемент не был 'освобождён'\n");
                else
                    output_pointer_stack(pointer_stack);
            }
        }
        else if (flag == '4')
        {
            printf("Введите строку:");
            getchar();
            while (1)
            {
                if (scanf("%c", &symb) != 1)
                {
                    free(char_stack_b);
                    free_stack(main_stack);
                    free_stack(second_stack);
                    free_pointer_stack(pointer_stack);
                    printf("Некорректный ввод!\n");
                    return INPUT_FAIL;
                }
                if (symb == '\n' || symb == '\0' || symb == ' ')
                    break;
                if (main_stack->size == MAX)
                {
                    printf("Достигнут максимум элементов, не все элементы будут добавлены в стек!\n");
                    break;
                }
                else
                {
                    push_stack_array(char_stack_b, size_of_stack, symb);
                    push_stack(main_stack, symb);
                    size_of_stack++;
                }
            }
        }
        else if (flag == '5')
        {
            getchar();
            if (main_stack->head != NULL)
            {
                check = check_for_palindrom_array(char_stack_b, size_of_stack);
                if (check_for_palindrom(main_stack, second_stack, pointer_stack) && check == 1)
                {
                    size_of_stack = 0;
                    printf("Строка является палиндромом!\n");
                }
                else
                {
                    size_of_stack = check;
                    printf("Строка не является палиндромом!\n");
                }
            }
            else
                printf("Стэк пуст!\n");
        }
        else if (flag == '6')
        {
            printf("Результат сравнения:\n");
            printf("Кол-во элементов   |    Время на push/pop для массива |  Время на push/pop для списка  |   Эффективность по времени  |  Память под список  |  Память под массив  |  Эффективность по памяти |\n");
            ////
            printf("     10             ");
            third_stack = allocate_stack();
            int read_size = sizeof (stack_t) + sizeof (element_t) * 10;
            int arr_size = sizeof (char) * MAX;
            char *second_char_stack_b = (char*)malloc(sizeof(char) * MAX);
            clock_t time_ten_start = clock();
            for (int i = 0; i < ITERATIONS; i++)
                for (int j = 0; j < 10; j++)
                {
                    push_stack(third_stack, 'K');
                    pop_stack(third_stack);
                }
            clock_t time_ten_finish = clock() - time_ten_start;

            clock_t time_ten_ar_start = clock();
            for (int i = 0; i < ITERATIONS; i++)
                for (int j = 0; j < 10; j++)
                {
                    push_stack_array(second_char_stack_b, 10, 'K');
                    pop_stack_array(second_char_stack_b, 10);
                }
            clock_t time_ten_ar_finish = clock() - time_ten_ar_start;
            printf("         %g  ", (double) time_ten_ar_finish / CLOCKS_PER_SEC / ITERATIONS);
            printf("                    %g  ", (double) time_ten_finish / CLOCKS_PER_SEC / ITERATIONS);
            printf("                   %g   ",  (double) time_ten_finish/time_ten_ar_finish);
            printf("                    %d                  %d    ", read_size, arr_size);
            printf("               %g   \n", (double) read_size/arr_size);
            ////
            printf("     15             ");
            free_stack(third_stack);
            third_stack = allocate_stack();
            read_size = sizeof (stack_t) + sizeof (element_t) * 15;
            free(second_char_stack_b);
            second_char_stack_b = (char*)malloc(sizeof(char) * MAX);
            clock_t time_fifteen_start = clock();
            for (int i = 0; i < ITERATIONS; i++)
                for (int j = 0; j < 15; j++)
                {
                    push_stack(third_stack, 'K');
                    pop_stack(third_stack);
                }
            clock_t time_fifteen_finish = clock() - time_fifteen_start;

            clock_t time_fifteen_ar_start = clock();
            for (int i = 0; i < ITERATIONS; i++)
                for (int j = 0; j < 15; j++)
                {
                    push_stack_array(second_char_stack_b, 15, 'K');
                    pop_stack_array(second_char_stack_b, 15);
                }
            clock_t time_fifteen_ar_finish = clock() - time_fifteen_ar_start;
            printf("         %g  ", (double) time_fifteen_ar_finish / CLOCKS_PER_SEC / ITERATIONS);
            printf("                   %g  ", (double) time_fifteen_finish / CLOCKS_PER_SEC / ITERATIONS);
            printf("                    %g   ",  (double) time_fifteen_finish/time_fifteen_ar_finish);
            printf("                   %d                  %d    ", read_size, arr_size);
            printf("               %g   \n", (double) read_size/arr_size);
            ////
            printf("     20             ");
            free_stack(third_stack);
            third_stack = allocate_stack();
            read_size = sizeof (stack_t) + sizeof (element_t) * 20;
            free(second_char_stack_b);
            second_char_stack_b = (char*)malloc(sizeof(char) * MAX);
            clock_t time_twenty_start = clock();
            for (int i = 0; i < ITERATIONS; i++)
                for (int j = 0; j < 20; j++)
                {
                    push_stack(third_stack, 'K');
                    pop_stack(third_stack);
                }
            clock_t time_twenty_finish = clock() - time_twenty_start;

            clock_t time_twenty_ar_start = clock();
            for (int i = 0; i < ITERATIONS; i++)
                for (int j = 0; j < 20; j++)
                {
                    push_stack_array(second_char_stack_b, 20, 'K');
                    pop_stack_array(second_char_stack_b, 20);
                }
            clock_t time_twenty_ar_finish = clock() - time_twenty_ar_start;
            printf("         %g  ", (double) time_twenty_ar_finish / CLOCKS_PER_SEC / ITERATIONS);
            printf("                   %g  ", (double) time_twenty_finish / CLOCKS_PER_SEC / ITERATIONS);
            printf("                   %g   ",  (double) time_twenty_finish/time_twenty_ar_finish);
            printf("                   %d                  %d    ", read_size, arr_size);
            printf("               %g   \n", (double) read_size/arr_size);
            ////
            printf("     25             ");
            free_stack(third_stack);
            third_stack = allocate_stack();
            read_size = sizeof (stack_t) + sizeof (element_t) * 25;
            free(second_char_stack_b);
            second_char_stack_b = (char*)malloc(sizeof(char) * MAX);
            clock_t time_twenty_five_start = clock();
            for (int i = 0; i < ITERATIONS; i++)
                for (int j = 0; j < 25; j++)
                {
                    push_stack(third_stack, 'K');
                    pop_stack(third_stack);
                }
            clock_t time_twenty_five_finish = clock() - time_twenty_five_start;

            clock_t time_twenty_five_ar_start = clock();
            for (int i = 0; i < ITERATIONS; i++)
                for (int j = 0; j < 20; j++)
                {
                    push_stack_array(second_char_stack_b, 25, 'K');
                    pop_stack_array(second_char_stack_b, 25);
                }
            clock_t time_twenty_five_ar_finish = clock() - time_twenty_five_ar_start;
            printf("         %g  ", (double) time_twenty_five_ar_finish / CLOCKS_PER_SEC / ITERATIONS);
            printf("                   %g  ", (double) time_twenty_five_finish / CLOCKS_PER_SEC / ITERATIONS);
            printf("                   %g   ",  (double) time_twenty_five_finish/time_twenty_five_ar_finish);
            printf("                   %d                  %d    ", read_size, arr_size);
            printf("               %g   \n", (double) read_size/arr_size);
            getchar();
        }
        else if (flag == '0')
        {
            getchar();
            free(char_stack_b);
            free_stack(main_stack);
            free_stack(second_stack);
            free_pointer_stack(pointer_stack);
            return 0;
        }
        else
        {
            free(char_stack_b);
            free_stack(main_stack);
            free_stack(second_stack);
            free_pointer_stack(pointer_stack);
            printf("Некорректный ввод!\n");
            return INPUT_FAIL;
        }
    }
}


