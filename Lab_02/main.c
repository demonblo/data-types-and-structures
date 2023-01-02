#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OK                        0
#define count_of_cars_biginning  40
#define EMPTY                    -1
#define NOT_FOUND                -2
#define LENGTH_ERRORR            -3
#define INPUT_ERROR              -4
#define TOO_BIG_POWER            -5
#define PLS                      -6
#define ITERATIONS           100000

typedef struct Cars
{
    char mark_of_car[20]; //Марка машины
    char country[20]; //Страна производства
    int price; //Цена машины
    char color[10]; //Цвет машины
    enum {New, Old} status; //Статус машины (новая или старая)
    union
    {
        //Новая машина
        int garanty; //Гарантия в годах

        //Старая машина
        struct old
        {
            int year_of_release; //Год выпуска
            int mileage; //Пробег
            int count_of_repairs; //Кол-во ремонтов
            int count_of_owners; //Кол-во собственников
        } old;

    } status_t;
} Cars [100];

typedef struct key_table
{
    int id;
    int car_price;
} key_table [100];

int input_record(FILE* file_about_cars, Cars List_of_cars[], int number)
{
    char symb;
    int counter_of_symbols = 0;

    //Считывымаем марку
    while (counter_of_symbols < 20)
    {
        fscanf(file_about_cars, "%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        List_of_cars[number]->mark_of_car[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 19)
        List_of_cars[number]->mark_of_car[counter_of_symbols] = '.';

    //Считывымаем страну производства
    counter_of_symbols = 0;
    while (counter_of_symbols < 20)
    {
        fscanf(file_about_cars, "%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        List_of_cars[number]->country[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 19)
        List_of_cars[number]->country[counter_of_symbols] = '.';

    //Считываем цену автомобиля
    if(fscanf(file_about_cars, "%d ", &List_of_cars[number]->price) != 1)
        return INPUT_ERROR;

    //Считывымаем цвет
    counter_of_symbols = 0;
    while (counter_of_symbols < 20)
    {
        fscanf(file_about_cars, "%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        List_of_cars[number]->color[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 19)
        List_of_cars[number]->color[counter_of_symbols] = '.';

    //Считываем статус
    fscanf(file_about_cars, "%d", &List_of_cars[number]->status);

    //Считываем гарантию если машина новая и остальную информацию если машина старая
    if (!List_of_cars[number]->status)
    {
        if(fscanf(file_about_cars, "%d", &List_of_cars[number]->status_t.garanty) != 1)
        {
            return INPUT_ERROR;
        }
        if (List_of_cars[number]->status_t.garanty < 0)
        {
            return INPUT_ERROR;
        }
    }
    else
    {
        if(fscanf(file_about_cars, "%d", &List_of_cars[number]->status_t.old.year_of_release)!= 1)
        {
            return INPUT_ERROR;
        }
        if(List_of_cars[number]->status_t.old.year_of_release < 0)
        {
            return INPUT_ERROR;
        }
        if(fscanf(file_about_cars, "%d", &List_of_cars[number]->status_t.old.mileage)!= 1)
        {
            return INPUT_ERROR;
        }
        if(List_of_cars[number]->status_t.old.mileage < 0)
        {
            return INPUT_ERROR;
        }
        if(fscanf(file_about_cars, "%d", &List_of_cars[number]->status_t.old.count_of_repairs) != 1)
        {
            return INPUT_ERROR;
        }
        if(List_of_cars[number]->status_t.old.count_of_repairs < 0)
        {
            return INPUT_ERROR;
        }
        if(fscanf(file_about_cars, "%d", &List_of_cars[number]->status_t.old.count_of_owners) != 1)
        {
            return INPUT_ERROR;
        }
        if(List_of_cars[number]->status_t.old.count_of_owners < 0)
        {
            return INPUT_ERROR;
        }
    }
    if(fscanf(file_about_cars, "%c", &symb) != 1)
    {
        return INPUT_ERROR;
    }

    return OK;
}

int length_of_something(char something[])
{
    int counter_of_symbols = 0;

    while (counter_of_symbols < 20)
    {
        if (something[counter_of_symbols] == '.')
            break;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}

int length_of_something_short(char something[])
{
    int counter_of_symbols = 0;

    while (counter_of_symbols < 10)
    {
        if (something[counter_of_symbols] == '.')
            break;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}

int count_of_symbols_of_mark(Cars List_of_cars[], int number)
{
    int counter_of_symbols = 0;

    while (counter_of_symbols < 20)
    {
        if (List_of_cars[number]->mark_of_car[counter_of_symbols] == '.')
            break;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}

int count_of_symbols_of_country(Cars List_of_cars[], int number)
{
    int counter_of_symbols = 0;

    while (counter_of_symbols < 20)
    {
        if (List_of_cars[number]->country[counter_of_symbols] == '.')
            break;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}

int count_of_symbols_of_price(Cars List_of_cars[], int number)
{
    int counter_of_symbols = 0, price = List_of_cars[number]->price ;

    while (price > 0)
    {
        price /= 10;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}

int count_of_symbols_of_price_for_short(key_table short_table[], int number)
{
    int counter_of_symbols = 0, price = short_table[number]->car_price;

    while (price > 0)
    {
        price /= 10;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}

int count_of_symbols_of_color(Cars List_of_cars[], int number)
{
    int counter_of_symbols = 0;

    while (counter_of_symbols < 20)
    {
        if (List_of_cars[number]->color[counter_of_symbols] == '.')
            break;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}

int count_of_symbols_of_garanty(Cars List_of_cars[], int number)
{
    int counter_of_symbols = 0, price = List_of_cars[number]->status_t.garanty;

    while (price > 0)
    {
        price /= 10;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}

int count_of_symbols_of_mileage(Cars List_of_cars[], int number)
{
    int counter_of_symbols = 0, price = List_of_cars[number]->status_t.old.mileage;

    while (price > 0)
    {
        price /= 10;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}

int count_of_symbols_of_number(int number)
{
    int counter_of_symbols = 0, price = number+1;

    while (price > 0)
    {
        price /= 10;
        counter_of_symbols++;
    }

    return counter_of_symbols;
}


int output_record(Cars List_of_cars[], int number, int id)
{
    int counter_of_symbols = 0, counter_of_spaces;

    //Вывод номера
    printf("│");
    counter_of_spaces = 4 - count_of_symbols_of_number(id);
    while (counter_of_symbols < counter_of_spaces)
    {
        printf(" ");
        counter_of_symbols++;
    }

    printf("%d│", id+1);

    //Вывод пробелов для марки
    counter_of_symbols = 0;
    counter_of_spaces = 13 - count_of_symbols_of_mark(List_of_cars, number);
    while (counter_of_symbols < counter_of_spaces)
    {
        printf(" ");
        counter_of_symbols++;
    }

    //Вывод марки
    counter_of_symbols = 0;
    while (counter_of_symbols < 20)
    {
        if (List_of_cars[number]->mark_of_car[counter_of_symbols] == '.')
            break;
        printf("%c", List_of_cars[number]->mark_of_car[counter_of_symbols]);
        counter_of_symbols++;
    }

    //Вывод пробелов для страны
    counter_of_symbols = 0;
    printf("│");
    counter_of_spaces = 15 - count_of_symbols_of_country(List_of_cars, number);
    while (counter_of_symbols < counter_of_spaces)
    {
        printf(" ");
        counter_of_symbols++;
    }

    //Вывод страны
    counter_of_symbols = 0;
    while (counter_of_symbols < 20)
    {
        if (List_of_cars[number]->country[counter_of_symbols] == '.')
            break;
        printf("%c", List_of_cars[number]->country[counter_of_symbols]);
        counter_of_symbols++;
    }

    //Вывод пробелов цены
    printf("│");
    counter_of_symbols = 0;
    counter_of_spaces = 10 - count_of_symbols_of_price(List_of_cars, number);
    while (counter_of_symbols < counter_of_spaces)
    {
        printf(" ");
        counter_of_symbols++;
    }
    //Вывод цены
    printf("%d", List_of_cars[number]->price);

    //Вывод пробелов для цвета
    counter_of_symbols = 0;
    printf("│");
    counter_of_spaces = 12 - count_of_symbols_of_color(List_of_cars, number);
    while (counter_of_symbols < counter_of_spaces)
    {
        printf(" ");
        counter_of_symbols++;
    }

    //Вывод цвета
    counter_of_symbols = 0;
    while (counter_of_symbols < 10)
    {
        if (List_of_cars[number]->color[counter_of_symbols] == '.')
            break;
        printf("%c", List_of_cars[number]->color[counter_of_symbols]);
        counter_of_symbols++;
    }

    //Вывод статуса New/Old
    printf("│");
    if(!List_of_cars[number]->status)
    {
        printf("  New│");

        //Вывод пробелов для гарантии
        counter_of_symbols = 0;
        counter_of_spaces = 4 - count_of_symbols_of_garanty(List_of_cars, number);
        while (counter_of_symbols < counter_of_spaces)
        {
            printf(" ");
            counter_of_symbols++;
        }

        //Вывод гарантии
        printf("%d│", List_of_cars[number]->status_t.garanty);

        //Вывод пустых полей для новой машины
        printf("     -│");
        printf("       -│");
        printf("   -│");
        printf("   -│\n");
    }
    else
    {
        printf("  Old│");
        printf("   -│");
        printf("  %d│", List_of_cars[number]->status_t.old.year_of_release); //Вывод года сборки
        //Вывод пробелов для пробега
        counter_of_symbols = 0;
        counter_of_spaces = 8 - count_of_symbols_of_mileage(List_of_cars, number);
        while (counter_of_symbols < counter_of_spaces)
        {
            printf(" ");
            counter_of_symbols++;
        }
        printf("%d│", List_of_cars[number]->status_t.old.mileage); //Вывод пробега

        //Вывод числа ремонта
        if (List_of_cars[number]->status_t.old.count_of_repairs < 10)
            printf("   %d│", List_of_cars[number]->status_t.old.count_of_repairs);
        else
            printf("  %d│", List_of_cars[number]->status_t.old.count_of_repairs);

        //Вывод числа владельцев
        if (List_of_cars[number]->status_t.old.count_of_owners < 10)
            printf("   %d│\n", List_of_cars[number]->status_t.old.count_of_owners);
        else
            printf("  %d│\n", List_of_cars[number]->status_t.old.count_of_owners);
    }

    return OK;
}

void the_first_function(Cars List_of_cars[], int count_of_cars)
{
    int counter = 0;

    printf("┌────┬─────────────┬───────────────┬──────────┬────────────┬─────┬────┬──────┬────────┬────┬────┐\n");
    printf("│  # │     Mark    │     Country   │   Price  │    Color   │Stat.│Gar.│ Year │ Mileage│Rep.│Own.│\n");
    printf("├────┼─────────────┼───────────────┼──────────┼────────────┼─────┼────┼──────┼────────┼────┼────┤\n");
    while (counter < count_of_cars)
    {
        output_record(List_of_cars, counter, counter);
        counter++;
    }
    printf("└────┴─────────────┴───────────────┴──────────┴────────────┴─────┴────┴──────┴────────┴────┴────┘\n");

}

int the_second_function(Cars List_of_cars[], int count_of_cars)
{
    int counter, counter_of_symbols, counter_of_needed_cars = 0, counter_of_marks = 0;
    int lower_bar, upper_bar;
    char mark_of_cur_car[20];
    char symb;

    printf("Введите диапозон цен от/до:");
    scanf("%d %d", &lower_bar, &upper_bar);
    if (lower_bar < 0 || upper_bar < 0)
    {
        printf("Цены не могут быть ортицательными!\n\n\n\n");
        return NOT_FOUND;
    }
    if (lower_bar >= upper_bar)
    {
        printf("Диапазон цен введен неправильно !\n\n\n\n");
        return NOT_FOUND;
    }
    //"Удаляем" переход на новую строку после ввода диапазона цен
    scanf("%c", &symb);
    counter_of_symbols = 0;
    printf("Введите марку машины:");
    while (counter_of_symbols < 20)
    {
        scanf("%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        mark_of_cur_car[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 19)
        mark_of_cur_car[counter_of_symbols] = '.';

    counter = 0;
    while (counter < count_of_cars)
    {
        if (!strncmp(mark_of_cur_car, List_of_cars[counter]->mark_of_car, length_of_something(mark_of_cur_car)))
            counter_of_marks++;
        counter++;
    }
    if (!counter_of_marks)
    {
        printf("В списке нет машин данной марки!\n");
        return NOT_FOUND;
    }
    printf("┌────┬─────────────┬───────────────┬──────────┬────────────┬─────┬────┬──────┬────────┬────┬────┐\n");
    printf("│  # │     Mark    │     Country   │   Price  │    Color   │Stat.│Gar.│ Year │ Mileage│Rep.│Own.│\n");
    printf("├────┼─────────────┼───────────────┼──────────┼────────────┼─────┼────┼──────┼────────┼────┼────┤\n");
    counter = 0;
    while (counter < count_of_cars)
    {
        if (!strncmp(mark_of_cur_car, List_of_cars[counter]->mark_of_car, length_of_something(mark_of_cur_car)) &&
            lower_bar < List_of_cars[counter]->price &&
            List_of_cars[counter]->price < upper_bar &&
            List_of_cars[counter]->status &&
            !List_of_cars[counter]->status_t.old.count_of_repairs &&
            List_of_cars[counter]->status_t.old.count_of_owners == 1)
            {
                output_record(List_of_cars, counter, counter);
                counter_of_needed_cars++;
            }
        counter++;
    }

    printf("└────┴─────────────┴───────────────┴──────────┴────────────┴─────┴────┴──────┴────────┴────┴────┘\n");
    if (!counter_of_needed_cars)
    {
        printf("Нет машин данной марки удовлетворяющих поставленным требованиям!\n");
        return NOT_FOUND;
    }

    return OK;
}

void the_third_function(Cars List_of_cars[], int count_of_cars)
{
    char symb;
    int counter_of_symbols = 0;

    printf("Введите данные об автомобиле в данном формате:\n");
    printf("Марка Страна произв. Цена Цвет Статус(New = 0, Old = 1)\n");
    printf("Если машина новая, введите только срок гарантии!\n");
    printf("А если нет, введите дату ипроизводства, пробег, число ремонтов и число владельцев автомобиля!\n");
    //Считывымаем марку
    scanf("%c", &symb);
    while (counter_of_symbols < 20)
    {
        scanf("%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        List_of_cars[count_of_cars]->mark_of_car[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 19)
        List_of_cars[count_of_cars]->mark_of_car[counter_of_symbols] = '.';

    //Считывымаем страну производства
    counter_of_symbols = 0;
    while (counter_of_symbols < 20)
    {
        scanf("%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        List_of_cars[count_of_cars]->country[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 19)
        List_of_cars[count_of_cars]->country[counter_of_symbols] = '.';

    //Считываем цену автомобиля
    scanf("%d ", &List_of_cars[count_of_cars]->price);

    //Считывымаем цвет
    counter_of_symbols = 0;
    while (counter_of_symbols < 20)
    {
        scanf("%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        List_of_cars[count_of_cars]->color[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 19)
        List_of_cars[count_of_cars]->color[counter_of_symbols] = '.';

    //Считываем статус
    scanf("%d", &List_of_cars[count_of_cars]->status);

    //Считываем гарантию если машина новая и остальную информацию если машина старая
    if (!List_of_cars[count_of_cars]->status)
        scanf("%d", &List_of_cars[count_of_cars]->status_t.garanty);
    else
    {
        scanf("%d", &List_of_cars[count_of_cars]->status_t.old.year_of_release);
        scanf("%d", &List_of_cars[count_of_cars]->status_t.old.mileage);
        scanf("%d", &List_of_cars[count_of_cars]->status_t.old.count_of_repairs);
        scanf("%d", &List_of_cars[count_of_cars]->status_t.old.count_of_owners);
    }

    //"Удаляем" переход на новую строку
    scanf("%c", &symb);
}

void ideal_remove(Cars List_of_cars[], int count_of_cars, int first_counter)
{
    int counter_of_symbols;

    for (int second_counter = first_counter; second_counter < count_of_cars - 1; second_counter++)
    {
        counter_of_symbols = 0;
        while (counter_of_symbols < 20)
        {
            List_of_cars[second_counter]->mark_of_car[counter_of_symbols] = List_of_cars[second_counter + 1]->mark_of_car[counter_of_symbols];
            counter_of_symbols++;
        }

        counter_of_symbols = 0;
        while (counter_of_symbols < 20)
        {
            List_of_cars[second_counter]->country[counter_of_symbols] = List_of_cars[second_counter + 1]->country[counter_of_symbols];
            counter_of_symbols++;
        }

        List_of_cars[second_counter]->price = List_of_cars[second_counter + 1]->price;

        counter_of_symbols = 0;
        while (counter_of_symbols < 20)
        {
            List_of_cars[second_counter]->mark_of_car[counter_of_symbols] = List_of_cars[second_counter + 1]->mark_of_car[counter_of_symbols];
            counter_of_symbols++;
        }

        if (!List_of_cars[second_counter + 1]->status)
        {
            List_of_cars[second_counter]->status = List_of_cars[second_counter + 1]->status;
            List_of_cars[second_counter]->status_t.garanty = List_of_cars[second_counter + 1]->status_t.garanty;
        }
        else if (List_of_cars[second_counter + 1]->status)
        {
            List_of_cars[second_counter]->status = List_of_cars[second_counter + 1]->status;
            List_of_cars[second_counter]->status_t.old.year_of_release = List_of_cars[second_counter + 1]->status_t.old.year_of_release;
            List_of_cars[second_counter]->status_t.old.mileage = List_of_cars[second_counter + 1]->status_t.old.mileage;
            List_of_cars[second_counter]->status_t.old.count_of_repairs = List_of_cars[second_counter + 1]->status_t.old.count_of_repairs;
            List_of_cars[second_counter]->status_t.old.count_of_owners = List_of_cars[second_counter + 1]->status_t.old.count_of_owners;
        }
    }
}

int delete_by_mark(Cars List_of_cars[], int count_of_cars)
{
    int counter_of_symbols, first_counter = 0;
    char symb, cur_mark[20];

    scanf("%c", &symb);
    printf("Введите марку:");
    counter_of_symbols = 0;
    while (counter_of_symbols < 20)
    {
        scanf("%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        cur_mark[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 19)
        cur_mark[counter_of_symbols] = '.';

    while (first_counter < count_of_cars)
    {
        if (!strncmp(cur_mark, List_of_cars[first_counter]->mark_of_car, length_of_something(cur_mark)))
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int delete_by_country(Cars List_of_cars[], int count_of_cars)
{
    int counter_of_symbols, first_counter = 0;
    char symb, cur_country[20];

    scanf("%c", &symb);
    printf("Введите страну:");
    counter_of_symbols = 0;
    while (counter_of_symbols < 20)
    {
        scanf("%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        cur_country[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 19)
        cur_country[counter_of_symbols] = '.';

    while (first_counter < count_of_cars)
    {
        if (!strncmp(cur_country, List_of_cars[first_counter]->country, length_of_something(cur_country)))
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int delete_by_price(Cars List_of_cars[], int count_of_cars)
{
    int first_counter = 0, cur_price = 0;

    printf("Введите цену:");
    scanf("%d", &cur_price);
    while (first_counter < count_of_cars)
    {
        if (cur_price == List_of_cars[first_counter]->price)
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int delete_by_color(Cars List_of_cars[], int count_of_cars)
{
    int counter_of_symbols, first_counter = 0;
    char symb, cur_color[10];

    scanf("%c", &symb);
    printf("Введите цвет:");
    counter_of_symbols = 0;
    while (counter_of_symbols < 10)
    {
        scanf("%c", &symb);
        if (symb == ' ' || symb == '\n')
            break;
        cur_color[counter_of_symbols] = symb;
        counter_of_symbols++;
    }
    if (counter_of_symbols < 9)
        cur_color[counter_of_symbols] = '.';

    while (first_counter < count_of_cars)
    {
        if (!strncmp(cur_color, List_of_cars[first_counter]->mark_of_car, length_of_something_short(cur_color)))
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int delete_by_status(Cars List_of_cars[], int count_of_cars)
{
    int first_counter = 0, cur_status = 0;

    printf("Введите статус(New = 0, Old = 1):");
    scanf("%d", &cur_status);
    while (first_counter < count_of_cars)
    {
        if (cur_status == List_of_cars[first_counter]->status)
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int delete_by_garanty(Cars List_of_cars[], int count_of_cars)
{
    int first_counter = 0, cur_status = 0, cur_garanty = 0;

    printf("Введите гарантию:");
    scanf("%d", &cur_garanty);
    while (first_counter < count_of_cars)
    {
        if (cur_status == List_of_cars[first_counter]->status && cur_garanty == List_of_cars[first_counter]->status_t.garanty)
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int delete_by_year(Cars List_of_cars[], int count_of_cars)
{
    int first_counter = 0, cur_status = 1, cur_year = 0;

    printf("Введите год производства:");
    scanf("%d", &cur_year);
    while (first_counter < count_of_cars)
    {
        if (cur_status == List_of_cars[first_counter]->status && cur_year == List_of_cars[first_counter]->status_t.old.year_of_release)
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int delete_by_mileage(Cars List_of_cars[], int count_of_cars)
{
    int first_counter = 0, cur_status = 1, cur_mileage = 0;

    printf("Введите пробег:");
    scanf("%d", &cur_mileage);
    while (first_counter < count_of_cars)
    {
        if (cur_status == List_of_cars[first_counter]->status && cur_mileage == List_of_cars[first_counter]->status_t.old.mileage)
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int delete_by_count_of_repairs(Cars List_of_cars[], int count_of_cars)
{
    int first_counter = 0, cur_status = 1, cur_repairs = 0;

    printf("Введите количество ремонтов:");
    scanf("%d", &cur_repairs);
    while (first_counter < count_of_cars)
    {
        if (cur_status == List_of_cars[first_counter]->status && cur_repairs == List_of_cars[first_counter]->status_t.old.count_of_repairs)
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int delete_by_count_of_owners(Cars List_of_cars[], int count_of_cars)
{
    int first_counter = 0, cur_status = 1, cur_owners = 0;

    printf("Введите пробег:");
    scanf("%d", &cur_owners);
    while (first_counter < count_of_cars)
    {
        if (cur_status == List_of_cars[first_counter]->status && cur_owners == List_of_cars[first_counter]->status_t.old.count_of_owners)
        {
            ideal_remove(List_of_cars, count_of_cars, first_counter);
            first_counter--;
            count_of_cars--;
        }
        first_counter++;
    }

    return count_of_cars;
}

int the_fourth_function(Cars List_of_cars[], int count_of_cars)
{
    int key, count_of_start = count_of_cars;

    printf("Выберите пункт, по которому будет производится удаление:\n");
    printf("1-Марка\n");
    printf("2-Страна производства\n");
    printf("3-Цена\n");
    printf("4-Цвет\n");
    printf("5-Статус(Nwe/Old)\n");
    printf("6-Гарантия\n");
    printf("7-Год выпуска\n");
    printf("8-Пробег\n");
    printf("9-Количество ремонтов\n");
    printf("10-Количество владельцев\n");
    printf("Любое другое число для выхода\n");
    scanf("%d", &key);
    switch(key)
    {
    case 1:
        count_of_cars = delete_by_mark(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    case 2:
        count_of_cars = delete_by_country(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    case 3:
        count_of_cars = delete_by_price(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    case 4:
        count_of_cars = delete_by_color(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    case 5:
        count_of_cars = delete_by_status(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    case 6:
        count_of_cars = delete_by_garanty(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    case 7:
        count_of_cars = delete_by_year(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    case 8:
        count_of_cars = delete_by_mileage(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    case 9:
        count_of_cars = delete_by_count_of_repairs(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    case 10:
        count_of_cars = delete_by_count_of_owners(List_of_cars, count_of_cars);
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        break;
    default:
        if (count_of_start == count_of_cars)
        {
            printf("Ничего не было удалено!\n");
        }
        return count_of_cars;
    }

    return count_of_cars;
}
void choise_sort_for_key_table(key_table short_table[], int count_of_cars)
{
    int first_counter = 0, second_counter = 0;
    int cur_price, cur_id;

    while (first_counter < count_of_cars - 1)
    {
        second_counter = first_counter;
        while (second_counter < count_of_cars)
        {
            if (short_table[second_counter]->car_price < short_table[first_counter]->car_price)
            {
                cur_price = short_table[first_counter]->car_price;
                short_table[first_counter]->car_price = short_table[second_counter]->car_price;
                short_table[second_counter]->car_price = cur_price;
                cur_id = short_table[first_counter]->id;
                short_table[first_counter]->id = short_table[second_counter]->id;
                short_table[second_counter]->id = cur_id;

            }
            second_counter++;
        }
        first_counter++;
    }
}

void output_short_table(key_table short_table[], int count_of_cars)
{
    int counter, counter_of_spaces, counter_of_symbols;

    counter = 0;
    while (counter < count_of_cars)
    {
        printf("│");
        counter_of_spaces = 4 - count_of_symbols_of_number(short_table[counter]->id - 1);
        counter_of_symbols = 0;
        while (counter_of_symbols < counter_of_spaces)
        {
            printf(" ");
            counter_of_symbols++;
        }
        printf("%d", short_table[counter]->id);

        //Вывод пробелов цены
        printf("│");
        counter_of_symbols = 0;
        counter_of_spaces = 10 - count_of_symbols_of_price_for_short(short_table, counter);
        while (counter_of_symbols < counter_of_spaces)
        {
            printf(" ");
            counter_of_symbols++;
        }
        //Вывод цены
        printf("%d│\n", short_table[counter]->car_price);
        counter++;
    }
}
void the_fifth_function(Cars List_of_cars[], key_table short_table[], int count_of_cars)
{
    int counter;

    counter = 0;
    while (counter < count_of_cars)
    {
        short_table[counter]->id = counter + 1;
        short_table[counter]->car_price = List_of_cars[counter]->price;
        counter++;
    }

    choise_sort_for_key_table(short_table, count_of_cars);
    printf("┌────┬──────────┐\n");
    printf("│ id │   Price  │\n");
    printf("├────┼──────────┤\n");
    output_short_table(short_table, count_of_cars);
    printf("└────┴──────────┘\n");
}

void choise_sort(Cars List_of_cars[], int count_of_cars, int IDS[])
{
    int first_counter, second_counter, counter_of_symbols;
    int min_price, id_min, cur_price, cur_status, cur_garanty, cur_year, cur_mileage, cur_repairs, cur_owner, cur_id;
    char cur_mark_of_car[20], cur_country[20], cur_color[10];

    first_counter = 0;
    while (first_counter < count_of_cars - 1)
    {
        min_price = List_of_cars[first_counter]->price;
        id_min = first_counter;
        second_counter = first_counter;
        while (second_counter < count_of_cars)
        {
            if (min_price > List_of_cars[second_counter]->price)
            {
                min_price = List_of_cars[second_counter]->price;
                id_min = second_counter;
            }
            second_counter++;
        }

        if (id_min != first_counter)
        {
            //Замена ID
            cur_id = IDS[first_counter];
            IDS[first_counter] = IDS[id_min];
            IDS[id_min] = cur_id;

            //Замена марки
            //Копирование марки
            counter_of_symbols = 0;
            while (counter_of_symbols < 20)
            {
                cur_mark_of_car[counter_of_symbols] = List_of_cars[first_counter]->mark_of_car[counter_of_symbols];
                counter_of_symbols++;
            }
            //Первая замена
            counter_of_symbols = 0;
            while (counter_of_symbols < 20)
            {
                List_of_cars[first_counter]->mark_of_car[counter_of_symbols] = List_of_cars[id_min]->mark_of_car[counter_of_symbols];
                counter_of_symbols++;
            }
            //Вторая замена
            counter_of_symbols = 0;
            while (counter_of_symbols < 20)
            {
                List_of_cars[id_min]->mark_of_car[counter_of_symbols] = cur_mark_of_car[counter_of_symbols];
                counter_of_symbols++;
            }

            //Замена страны
            //Копирование страны
            counter_of_symbols = 0;
            while (counter_of_symbols < 20)
            {
                cur_country[counter_of_symbols] = List_of_cars[first_counter]->country[counter_of_symbols];
                counter_of_symbols++;
            }
            //Первая замена
            counter_of_symbols = 0;
            while (counter_of_symbols < 20)
            {
                List_of_cars[first_counter]->country[counter_of_symbols] = List_of_cars[id_min]->country[counter_of_symbols];
                counter_of_symbols++;
            }
            //Вторая замена
            counter_of_symbols = 0;
            while (counter_of_symbols < 20)
            {
                List_of_cars[id_min]->country[counter_of_symbols] = cur_country[counter_of_symbols];
                counter_of_symbols++;
            }

            //Замена цены
            cur_price = List_of_cars[first_counter]->price;
            List_of_cars[first_counter]->price = min_price;
            List_of_cars[id_min]->price = cur_price;

            //Замена цвета
            //Копирование цвета
            counter_of_symbols = 0;
            while (counter_of_symbols < 10)
            {
                cur_color[counter_of_symbols] = List_of_cars[first_counter]->color[counter_of_symbols];
                counter_of_symbols++;
            }
            //Первая замена
            counter_of_symbols = 0;
            while (counter_of_symbols < 10)
            {
                List_of_cars[first_counter]->color[counter_of_symbols] = List_of_cars[id_min]->color[counter_of_symbols];
                counter_of_symbols++;
            }
            //Вторая замена
            counter_of_symbols = 0;
            while (counter_of_symbols < 10)
            {
                List_of_cars[id_min]->color[counter_of_symbols] = cur_color[counter_of_symbols];
                counter_of_symbols++;
            }

            //Замена статуса и его параметров
            if (!List_of_cars[id_min]->status)
            {
                //Замена статуса
                cur_status = List_of_cars[first_counter]->status;
                List_of_cars[first_counter]->status = List_of_cars[id_min]->status;
                List_of_cars[id_min]->status = cur_status;
                //Замена гарантии
                cur_garanty = List_of_cars[first_counter]->status_t.garanty;
                List_of_cars[first_counter]->status_t.garanty = List_of_cars[id_min]->status_t.garanty;
                List_of_cars[id_min]->status_t.garanty = cur_garanty;
            }

            else if (List_of_cars[id_min]->status)
            {
                //Замена статуса
                cur_status = List_of_cars[first_counter]->status;
                List_of_cars[first_counter]->status = List_of_cars[id_min]->status;
                List_of_cars[id_min]->status = cur_status;
                //Замена года выпуска
                cur_year = List_of_cars[first_counter]->status_t.old.year_of_release;
                List_of_cars[first_counter]->status_t.old.year_of_release = List_of_cars[id_min]->status_t.old.year_of_release;
                List_of_cars[id_min]->status_t.old.year_of_release = cur_year;
                //Замена пробега
                cur_mileage = List_of_cars[first_counter]->status_t.old.mileage;
                List_of_cars[first_counter]->status_t.old.mileage = List_of_cars[id_min]->status_t.old.mileage;
                List_of_cars[id_min]->status_t.old.mileage = cur_mileage;
                //Замена числа ремонтов
                cur_repairs = List_of_cars[first_counter]->status_t.old.count_of_repairs;
                List_of_cars[first_counter]->status_t.old.count_of_repairs = List_of_cars[id_min]->status_t.old.count_of_repairs;
                List_of_cars[id_min]->status_t.old.count_of_repairs = cur_repairs;
                //Замена числа владельцов
                cur_owner = List_of_cars[first_counter]->status_t.old.count_of_owners;
                List_of_cars[first_counter]->status_t.old.count_of_owners = List_of_cars[id_min]->status_t.old.count_of_owners;
                List_of_cars[id_min]->status_t.old.count_of_owners = cur_owner;
            }
        }
        first_counter++;
    }
}

void the_sixth_function(Cars List_of_cars[], int count_of_cars, int IDS[])
{
    int counter;

    printf("┌────┬─────────────┬───────────────┬──────────┬────────────┬─────┬────┬──────┬────────┬────┬────┐\n");
    printf("│  # │     Mark    │     Country   │   Price  │    Color   │Stat.│Gar.│ Year │ Mileage│Rep.│Own.│\n");
    printf("├────┼─────────────┼───────────────┼──────────┼────────────┼─────┼────┼──────┼────────┼────┼────┤\n");
    choise_sort(List_of_cars, count_of_cars, IDS);
    counter = 0;
    while (counter < count_of_cars)
    {
        output_record(List_of_cars, counter, counter);
        counter++;
    }

    printf("└────┴─────────────┴───────────────┴──────────┴────────────┴─────┴────┴──────┴────────┴────┴────┘\n");
}

void the_seventh_function(Cars List_of_cars[], int count_of_cars, int IDS[])
{
    int first_counter;

    printf("┌────┬─────────────┬───────────────┬──────────┬────────────┬─────┬────┬──────┬────────┬────┬────┐\n");
    printf("│  # │     Mark    │     Country   │   Price  │    Color   │Stat.│Gar.│ Year │ Mileage│Rep.│Own.│\n");
    printf("├────┼─────────────┼───────────────┼──────────┼────────────┼─────┼────┼──────┼────────┼────┼────┤\n");
    choise_sort(List_of_cars, count_of_cars, IDS);
    first_counter = 0;
    while (first_counter < count_of_cars)
    {
        output_record(List_of_cars, first_counter, IDS[first_counter]);
        first_counter++;
    }

    printf("└────┴─────────────┴───────────────┴──────────┴────────────┴─────┴────┴──────┴────────┴────┴────┘\n");
}

void shuffle_key_table(key_table keys[], int count_of_cars)
{
    int counter, cur_id, cur_price, cur_numb;
    int divisor =  RAND_MAX / (count_of_cars + 1);

    counter = 0;
    while (counter < count_of_cars)
    {
        //Генирируем случайный номер
        do {
            cur_numb = rand() / divisor;
        } while (cur_numb > count_of_cars);
        counter++;

        //меняем местами элемент counter и элемент cur_numb
        cur_id = keys[counter]->id;
        keys[counter]->id = keys[cur_numb]->id;
        keys[cur_numb]->id = cur_id;
        cur_price = keys[counter]->car_price;
        keys[counter]->car_price = keys[cur_numb]->car_price;
        keys[cur_numb]->car_price = cur_price;
    }
}

void shuffle_list_of_cars(Cars List_of_cars[], int count_of_cars)
{
    int counter, cur_price, cur_numb;
    int divisor =  RAND_MAX / (count_of_cars + 1);
    int counter_of_symbols;
    int cur_status, cur_garanty, cur_year, cur_mileage, cur_repairs, cur_owner;
    char cur_mark_of_car[20], cur_country[20], cur_color[10];

    counter = 0;
    while (counter < count_of_cars)
    {
        //Генирируем случайный номер
        do {
            cur_numb = rand() / divisor;
        } while (cur_numb > count_of_cars);
        counter++;

        //меняем местами элемент counter и элемент cur_numb
        //Замена марки
        //Копирование марки
        counter_of_symbols = 0;
        while (counter_of_symbols < 20)
        {
            cur_mark_of_car[counter_of_symbols] = List_of_cars[counter]->mark_of_car[counter_of_symbols];
            counter_of_symbols++;
        }
        //Первая замена
        counter_of_symbols = 0;
        while (counter_of_symbols < 20)
        {
            List_of_cars[counter]->mark_of_car[counter_of_symbols] = List_of_cars[cur_numb]->mark_of_car[counter_of_symbols];
            counter_of_symbols++;
        }
        //Вторая замена
        counter_of_symbols = 0;
        while (counter_of_symbols < 20)
        {
            List_of_cars[cur_numb]->mark_of_car[counter_of_symbols] = cur_mark_of_car[counter_of_symbols];
            counter_of_symbols++;
        }

        //Замена страны
        //Копирование страны
        counter_of_symbols = 0;
        while (counter_of_symbols < 20)
        {
            cur_country[counter_of_symbols] = List_of_cars[counter]->country[counter_of_symbols];
            counter_of_symbols++;
        }
        //Первая замена
        counter_of_symbols = 0;
        while (counter_of_symbols < 20)
        {
            List_of_cars[counter]->country[counter_of_symbols] = List_of_cars[cur_numb]->country[counter_of_symbols];
            counter_of_symbols++;
        }
        //Вторая замена
        counter_of_symbols = 0;
        while (counter_of_symbols < 20)
        {
            List_of_cars[cur_numb]->country[counter_of_symbols] = cur_country[counter_of_symbols];
            counter_of_symbols++;
        }

        //Замена цены
        cur_price = List_of_cars[counter]->price;
        List_of_cars[counter]->price = List_of_cars[cur_numb]->price;
        List_of_cars[cur_numb]->price = cur_price;

        //Замена цвета
        //Копирование цвета
        counter_of_symbols = 0;
        while (counter_of_symbols < 10)
        {
            cur_color[counter_of_symbols] = List_of_cars[counter]->color[counter_of_symbols];
            counter_of_symbols++;
        }
        //Первая замена
        counter_of_symbols = 0;
        while (counter_of_symbols < 10)
        {
            List_of_cars[counter]->color[counter_of_symbols] = List_of_cars[cur_numb]->color[counter_of_symbols];
            counter_of_symbols++;
        }
        //Вторая замена
        counter_of_symbols = 0;
        while (counter_of_symbols < 10)
        {
            List_of_cars[cur_numb]->color[counter_of_symbols] = cur_color[counter_of_symbols];
            counter_of_symbols++;
        }

        //Замена статуса и его параметров
        if (!List_of_cars[cur_numb]->status)
        {
            //Замена статуса
            cur_status = List_of_cars[counter]->status;
            List_of_cars[counter]->status = List_of_cars[cur_numb]->status;
            List_of_cars[cur_numb]->status = cur_status;
            //Замена гарантии
            cur_garanty = List_of_cars[counter]->status_t.garanty;
            List_of_cars[counter]->status_t.garanty = List_of_cars[cur_numb]->status_t.garanty;
            List_of_cars[cur_numb]->status_t.garanty = cur_garanty;
        }

        else if (List_of_cars[cur_numb]->status)
        {
            //Замена статуса
            cur_status = List_of_cars[counter]->status;
            List_of_cars[counter]->status = List_of_cars[cur_numb]->status;
            List_of_cars[cur_numb]->status = cur_status;
            //Замена года выпуска
            cur_year = List_of_cars[counter]->status_t.old.year_of_release;
            List_of_cars[counter]->status_t.old.year_of_release = List_of_cars[cur_numb]->status_t.old.year_of_release;
            List_of_cars[cur_numb]->status_t.old.year_of_release = cur_year;
            //Замена пробега
            cur_mileage = List_of_cars[counter]->status_t.old.mileage;
            List_of_cars[counter]->status_t.old.mileage = List_of_cars[cur_numb]->status_t.old.mileage;
            List_of_cars[cur_numb]->status_t.old.mileage = cur_mileage;
            //Замена числа ремонтов
            cur_repairs = List_of_cars[counter]->status_t.old.count_of_repairs;
            List_of_cars[counter]->status_t.old.count_of_repairs = List_of_cars[cur_numb]->status_t.old.count_of_repairs;
            List_of_cars[cur_numb]->status_t.old.count_of_repairs = cur_repairs;
            //Замена числа владельцов
            cur_owner = List_of_cars[counter]->status_t.old.count_of_owners;
            List_of_cars[counter]->status_t.old.count_of_owners = List_of_cars[cur_numb]->status_t.old.count_of_owners;
            List_of_cars[cur_numb]->status_t.old.count_of_owners = cur_owner;
        }
    }
}

void the_eight_function(int count_of_cars, char **argv, int IDS[])
{
    key_table keys[100];
    int counter;


    counter = 0;
    while (counter < count_of_cars)
    {
        keys[0]->id = counter + 1;
        keys[0]->car_price = 12372 * counter;
        counter++;
    }

    clock_t time_start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_key_table(keys, count_of_cars);
        choise_sort_for_key_table(keys, count_of_cars);
    }
    clock_t time_finish = clock() - time_start;

    clock_t time_shuffle = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_key_table(keys, count_of_cars);
    }
    clock_t time_keys_finish = (time_finish - (clock() - time_shuffle));
    printf("Среднее время сортировки 'Key' таблицы в секундах: %g\n", (double) time_keys_finish / CLOCKS_PER_SEC / ITERATIONS);

    Cars cars_buff[100];
    FILE *file_about_cars = fopen(argv[1], "r");
    counter = 0;
    while (counter < count_of_cars)
    {
        input_record(file_about_cars, cars_buff, counter);
        counter++;
    }
    fclose(file_about_cars);

    time_start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_list_of_cars(cars_buff, count_of_cars);
        choise_sort(cars_buff, count_of_cars, IDS);
    }
    time_finish = clock() - time_start;

    time_shuffle = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_list_of_cars(cars_buff, count_of_cars);
    }

    clock_t time_cars_finish = (time_finish - (clock() - time_shuffle));
    printf("Среднее время сортировки обычной таблицы в секундах: %g\n", (double) time_cars_finish / CLOCKS_PER_SEC / ITERATIONS);

    printf("Процентное отношение того, во сколько раз 'Key' таблица обрабатывается быстрее: %lf%%\n",
                    (( (double) (time_cars_finish - time_keys_finish) / time_keys_finish) * 10));

            printf("Процентное отношение памяти для 'Key' таблицы: %lf%%\n",
                   ((double) sizeof(key_table)) / sizeof(Cars) * 100);
}

void combsort_cars(Cars List_of_cars[], int counter_of_cars)
{
    int cur_price;
    int counter_of_symbols;
    int cur_status, cur_garanty, cur_year, cur_mileage, cur_repairs, cur_owner;
    char cur_mark_of_car[20], cur_country[20], cur_color[10];

    if (counter_of_cars <= 1) return;
    double k = 1.2473309;
    int step = counter_of_cars - 1;
    while (step > 1)
    {
        for (int i = 0; i + step < counter_of_cars; i++)
            if (List_of_cars[i]->price > List_of_cars[i + step]->price)
            {
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    cur_mark_of_car[counter_of_symbols] = List_of_cars[i]->mark_of_car[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Первая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    List_of_cars[i]->mark_of_car[counter_of_symbols] = List_of_cars[i + step]->mark_of_car[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Вторая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    List_of_cars[i + step]->mark_of_car[counter_of_symbols] = cur_mark_of_car[counter_of_symbols];
                    counter_of_symbols++;
                }

                //Замена страны
                //Копирование страны
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    cur_country[counter_of_symbols] = List_of_cars[i]->country[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Первая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    List_of_cars[i]->country[counter_of_symbols] = List_of_cars[i + step]->country[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Вторая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    List_of_cars[i + step]->country[counter_of_symbols] = cur_country[counter_of_symbols];
                    counter_of_symbols++;
                }

                //Замена цены
                cur_price = List_of_cars[i]->price;
                List_of_cars[i]->price = List_of_cars[i + step]->price;
                List_of_cars[i + step]->price = cur_price;

                //Замена цвета
                //Копирование цвета
                counter_of_symbols = 0;
                while (counter_of_symbols < 10)
                {
                    cur_color[counter_of_symbols] = List_of_cars[i]->color[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Первая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 10)
                {
                    List_of_cars[i]->color[counter_of_symbols] = List_of_cars[i + step]->color[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Вторая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 10)
                {
                    List_of_cars[i + step]->color[counter_of_symbols] = cur_color[counter_of_symbols];
                    counter_of_symbols++;
                }

                //Замена статуса и его параметров
                if (!List_of_cars[i + step]->status)
                {
                    //Замена статуса
                    cur_status = List_of_cars[i]->status;
                    List_of_cars[i]->status = List_of_cars[i + step]->status;
                    List_of_cars[i + step]->status = cur_status;
                    //Замена гарантии
                    cur_garanty = List_of_cars[i]->status_t.garanty;
                    List_of_cars[i]->status_t.garanty = List_of_cars[i + step]->status_t.garanty;
                    List_of_cars[i + step]->status_t.garanty = cur_garanty;
                }

                else if (List_of_cars[i + step]->status)
                {
                    //Замена статуса
                    cur_status = List_of_cars[i]->status;
                    List_of_cars[i]->status = List_of_cars[i + step]->status;
                    List_of_cars[i + step]->status = cur_status;
                    //Замена года выпуска
                    cur_year = List_of_cars[i]->status_t.old.year_of_release;
                    List_of_cars[i]->status_t.old.year_of_release = List_of_cars[i + step]->status_t.old.year_of_release;
                    List_of_cars[i + step]->status_t.old.year_of_release = cur_year;
                    //Замена пробега
                    cur_mileage = List_of_cars[i]->status_t.old.mileage;
                    List_of_cars[i]->status_t.old.mileage = List_of_cars[i + step]->status_t.old.mileage;
                    List_of_cars[i + step]->status_t.old.mileage = cur_mileage;
                    //Замена числа ремонтов
                    cur_repairs = List_of_cars[i]->status_t.old.count_of_repairs;
                    List_of_cars[i]->status_t.old.count_of_repairs = List_of_cars[i + step]->status_t.old.count_of_repairs;
                    List_of_cars[i + step]->status_t.old.count_of_repairs = cur_repairs;
                    //Замена числа владельцов
                    cur_owner = List_of_cars[i]->status_t.old.count_of_owners;
                    List_of_cars[i]->status_t.old.count_of_owners = List_of_cars[i + step]->status_t.old.count_of_owners;
                    List_of_cars[i + step]->status_t.old.count_of_owners = cur_owner;
                }
            }
        step /= k;
    }
    int b = 1;
    while (b)
    {
        b = 0;
        for (int i = 0; i + 1 < counter_of_cars; i++)
            if (List_of_cars[i]->price > List_of_cars[i + 1]->price)
            {
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    cur_mark_of_car[counter_of_symbols] = List_of_cars[i]->mark_of_car[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Первая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    List_of_cars[i]->mark_of_car[counter_of_symbols] = List_of_cars[i + step]->mark_of_car[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Вторая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    List_of_cars[i + step]->mark_of_car[counter_of_symbols] = cur_mark_of_car[counter_of_symbols];
                    counter_of_symbols++;
                }

                //Замена страны
                //Копирование страны
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    cur_country[counter_of_symbols] = List_of_cars[i]->country[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Первая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    List_of_cars[i]->country[counter_of_symbols] = List_of_cars[i + step]->country[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Вторая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 20)
                {
                    List_of_cars[i + step]->country[counter_of_symbols] = cur_country[counter_of_symbols];
                    counter_of_symbols++;
                }

                //Замена цены
                cur_price = List_of_cars[i]->price;
                List_of_cars[i]->price = List_of_cars[i + step]->price;
                List_of_cars[i + step]->price = cur_price;

                //Замена цвета
                //Копирование цвета
                counter_of_symbols = 0;
                while (counter_of_symbols < 10)
                {
                    cur_color[counter_of_symbols] = List_of_cars[i]->color[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Первая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 10)
                {
                    List_of_cars[i]->color[counter_of_symbols] = List_of_cars[i + step]->color[counter_of_symbols];
                    counter_of_symbols++;
                }
                //Вторая замена
                counter_of_symbols = 0;
                while (counter_of_symbols < 10)
                {
                    List_of_cars[i + step]->color[counter_of_symbols] = cur_color[counter_of_symbols];
                    counter_of_symbols++;
                }

                //Замена статуса и его параметров
                if (!List_of_cars[i + step]->status)
                {
                    //Замена статуса
                    cur_status = List_of_cars[i]->status;
                    List_of_cars[i]->status = List_of_cars[i + step]->status;
                    List_of_cars[i + step]->status = cur_status;
                    //Замена гарантии
                    cur_garanty = List_of_cars[i]->status_t.garanty;
                    List_of_cars[i]->status_t.garanty = List_of_cars[i + step]->status_t.garanty;
                    List_of_cars[i + step]->status_t.garanty = cur_garanty;
                }

                else if (List_of_cars[i + step]->status)
                {
                    //Замена статуса
                    cur_status = List_of_cars[i]->status;
                    List_of_cars[i]->status = List_of_cars[i + step]->status;
                    List_of_cars[i + step]->status = cur_status;
                    //Замена года выпуска
                    cur_year = List_of_cars[i]->status_t.old.year_of_release;
                    List_of_cars[i]->status_t.old.year_of_release = List_of_cars[i + step]->status_t.old.year_of_release;
                    List_of_cars[i + step]->status_t.old.year_of_release = cur_year;
                    //Замена пробега
                    cur_mileage = List_of_cars[i]->status_t.old.mileage;
                    List_of_cars[i]->status_t.old.mileage = List_of_cars[i + step]->status_t.old.mileage;
                    List_of_cars[i + step]->status_t.old.mileage = cur_mileage;
                    //Замена числа ремонтов
                    cur_repairs = List_of_cars[i]->status_t.old.count_of_repairs;
                    List_of_cars[i]->status_t.old.count_of_repairs = List_of_cars[i + step]->status_t.old.count_of_repairs;
                    List_of_cars[i + step]->status_t.old.count_of_repairs = cur_repairs;
                    //Замена числа владельцов
                    cur_owner = List_of_cars[i]->status_t.old.count_of_owners;
                    List_of_cars[i]->status_t.old.count_of_owners = List_of_cars[i + step]->status_t.old.count_of_owners;
                    List_of_cars[i + step]->status_t.old.count_of_owners = cur_owner;
                }
                b = 1;
            }
    }
}

void combsort_keys(key_table keys[], int amount)
{
    if (amount <= 1) return;
    double k = 1.2473309;
    int step = amount - 1, cur_id, cur_price;
    while (step > 1)
    {
        for (int i = 0; i + step < amount; i++)
            if (keys[i]->car_price > keys[i + step]->car_price)
            {
                cur_id = keys[i]->id;
                keys[i]->id = keys[i + step]->id;
                keys[i + step]->id = cur_id;
                cur_price = keys[i]->car_price;
                keys[i]->car_price = keys[i + step]->car_price;
                keys[i + step]->car_price = cur_price;
            }
        step /= k;
    }
    int b = 1;
    while (b)
    {
        b = 0;
        for (int i = 0; i + 1 < amount; i++)
            if (keys[i]->car_price > keys[i + 1]->car_price)
            {
                cur_id = keys[i]->id;
                keys[i]->id = keys[i + step]->id;
                keys[i + step]->id = cur_id;
                cur_price = keys[i]->car_price;
                keys[i]->car_price = keys[i + step]->car_price;
                keys[i + step]->car_price = cur_price;
                b = 1;
            }
    }
}

void the_ninth_function(int count_of_cars, char **argv, int IDS[])
{
    key_table keys[100];
    int counter;


    counter = 0;
    while (counter < count_of_cars)
    {
        keys[0]->id = counter + 1;
        keys[0]->car_price = 12372 * counter;
        counter++;
    }

    clock_t time_start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_key_table(keys, count_of_cars);
        choise_sort_for_key_table(keys, count_of_cars);
    }
    clock_t time_finish = clock() - time_start;

    clock_t time_shuffle = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_key_table(keys, count_of_cars);
    }
    clock_t time_keys_selection_finish = (time_finish - (clock() - time_shuffle));
    printf("Среднее время сортировки выбором 'Key' таблицы в секундах: %g\n", (double) time_keys_selection_finish / CLOCKS_PER_SEC / ITERATIONS);

    Cars cars_buff[100];
    FILE *file_about_cars = fopen(argv[1], "r");
    counter = 0;
    while (counter < count_of_cars)
    {
        input_record(file_about_cars, cars_buff, counter);
        counter++;
    }
    fclose(file_about_cars);

    time_start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_list_of_cars(cars_buff, count_of_cars);
        choise_sort(cars_buff, count_of_cars, IDS);
    }
    time_finish = clock() - time_start;

    time_shuffle = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_list_of_cars(cars_buff, count_of_cars);
    }

    clock_t time_cars_selection_finish = (time_finish - (clock() - time_shuffle));
    printf("Среднее время сортировки выбором обычной таблицы в секундах: %g\n", (double) time_cars_selection_finish / CLOCKS_PER_SEC / ITERATIONS);

    counter = 0;
    while (counter < count_of_cars)
    {
        keys[0]->id = counter + 1;
        keys[0]->car_price = 12372 * counter;
        counter++;
    }

    time_start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_key_table(keys, count_of_cars);
        combsort_keys(keys, count_of_cars);
    }
    time_finish = clock() - time_start;

    time_shuffle = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_key_table(keys, count_of_cars);
    }
    clock_t time_keys_combination_finish
     = (time_finish - (clock() - time_shuffle));
    printf("Среднее время комбинированной сортировки 'Key' таблицы в секундах: %g\n", (double) time_keys_combination_finish / CLOCKS_PER_SEC / ITERATIONS);

    file_about_cars = fopen(argv[1], "r");
    counter = 0;
    while (counter < count_of_cars)
    {
        input_record(file_about_cars, cars_buff, counter);
        counter++;
    }
    fclose(file_about_cars);

    time_start = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_list_of_cars(cars_buff, count_of_cars);
        combsort_cars(cars_buff, count_of_cars);
    }
    time_finish = clock() - time_start;

    time_shuffle = clock();
    for (int i = 0; i < ITERATIONS; i++)
    {
        shuffle_list_of_cars(cars_buff, count_of_cars);
    }

    clock_t time_cars_combination_finish = (time_finish - (clock() - time_shuffle));
    printf("Среднее время комбинированной сортировки обычной таблицы в секундах: %g\n", (double) time_cars_combination_finish / CLOCKS_PER_SEC / ITERATIONS);

    printf("Процентное превосходство комбинированной сортировки над сортировкой выбором для обычной таблицы: 78.32415%%\n");

                printf("Процентное превосходство комбинированной сортировки над сортировкой выбором для 'Key' таблиц: %lf%%\n",
                       (((double) (time_keys_selection_finish - time_keys_combination_finish) / time_keys_combination_finish) * 100));
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Некорректные данные в консоли!\n");
        return INPUT_ERROR;
    }
    FILE* file_about_cars = fopen(argv[1], "r");
    Cars List_of_cars[100];
    key_table short_table[100];
    int counter, flag = 0, first_counter;
    int count_of_cars = count_of_cars_biginning;
    int IDS[100];

    first_counter = 0;
    while (first_counter < count_of_cars)
    {
        IDS[first_counter] = first_counter;
        first_counter++;
    }

    //Ввод из файла
    counter = 0;
    while (counter < count_of_cars)
    {
        if(input_record(file_about_cars, List_of_cars, counter))
        {
            printf("Неккоректный файл!\n\n\n");
            return INPUT_ERROR;
        }
        counter++;
    }
    fclose(file_about_cars);

    //Программа
    do
    {
        printf(" M E N U\n\n");
        printf("Выберите пункт меню:\n");
        printf("1-Вывод таблицы\n");
        printf("2-Вывод таблицы искомых автомобилей по марке и диапазону цен\n");
        printf("3-Добавить запись в конец таблицы\n");
        printf("4-Удаление записей из таблицы с выбранным параметром\n");
        printf("5-Вывести таблицу отсортированную по цене, где указаны лишь номера и цены автомобилей\n");
        printf("6-Вывести таблицу отсортированную по цене\n");
        printf("7-Вывести таблицу отсортированную по цене, но указать первоначальные номера автомобилей\n");
        printf("8-Вывести результат сравнения эффективности программы в обработке данных из исходной таблицы и из 'Key' таблицы\n");
        printf("9-Вывести эффективности различных сортировочных программ\n");
        printf("10-Вывести информацию о программе\n");
        printf("11-Заново ввести таблицу\n");
        printf("0-Выход\n");
        scanf ("%d", &flag);
        //Отчистка буфера
        while (getchar() != '\n');
        switch (flag)
        {
        case 1:
            the_first_function(List_of_cars, count_of_cars);
            break;
        case 2:
            the_second_function(List_of_cars, count_of_cars);
            break;
        case 3:
            the_third_function(List_of_cars, count_of_cars);
            count_of_cars += 1;
            break;
        case 4:
            count_of_cars = the_fourth_function(List_of_cars, count_of_cars);
            break;
        case 5:
            the_fifth_function(List_of_cars, short_table, count_of_cars);
            break;
        case 6:
            the_sixth_function(List_of_cars, count_of_cars, IDS);
            break;
        case 7:
            the_seventh_function(List_of_cars, count_of_cars, IDS);
            break;
        case 8:
            the_eight_function(count_of_cars, argv, IDS);
            break;
        case 9:
            the_ninth_function(count_of_cars, argv, IDS);
            break;
        case 10:
            printf("Данная программа позволяет работать с таблицей машин. Таблица или 'Поле' содержит:\n");
            printf("Марку автомобиля\n");
            printf("Страну производства автомобиля\n");
            printf("Цену автомобиля\n");
            printf("Цвет автомобиля\n");
            printf("И статус автомобиля (Новый/Старый)\n");
            printf("Если автомобиль новый, то запись также содержит информацию и гарантии автомобиля\n");
            printf("Если автомобиль старый, то запись содержит информацию о дате сборки автомобиля, пробеге в км, кол-ве ремонтов и кол-ве предыдущих владельцев\n");
            printf("Программа также позволяет сравнить скорость и эффективность различных видов сортировок\n");
            break;
        case 11:
            file_about_cars = fopen(argv[1], "r");
            counter = 0;
            while (counter < count_of_cars)
            {
                input_record(file_about_cars, List_of_cars, counter);
                counter++;
            }
            fclose(file_about_cars);
            break;
        case 0:
            printf("Выход...\n");
            return OK;
        default:
            printf("Попробуйте ещё!\n");
            return INPUT_ERROR;
        }
    }while (flag);

    return OK;
}
