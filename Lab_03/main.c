#include "head.h"

int main(void)
{
    int choice;
    int flag_try_again = 0;
    int flag_starting_menu = 1;


    if (flag_starting_menu)
        while (1)
        {
            fflush(stdin);
            UI:
            if (flag_try_again)
            {
                printf("\nПопробуйте снова.\n");
            }
            printf("\nMAIN MENU: \n");
            printf("1) 'Классический' ввод матрицы\n");
            printf("2) Ввод матрицы по координатам\n");
            printf("3) Автоматический ввод матрицы\n");
            printf("0) Выход\n");

            if (!scanf("%d", &choice))
            {
                printf("\nНекорректный ввод!\n");
                break;
            }

            if ((choice > 3) || (choice < 0))
            {
                printf("Такого пункта в меню нет!\n");
                flag_try_again = 1;
                goto UI;
            }

            if (choice == 1)
            {
                int row = 0;
                int col = 0;

                printf("\nМаксимальная размерность матрицы 1000х1000!\n");

                UI1:
                printf("Введите количество строк матрицы: ");

                if (!scanf("%d", &row))
                {
                    printf("Некорректный ввод!\n");
                    break;
                }

                if (row <= 0)
                {
                    printf("\nРазмерность матрицы не может быть отрицательной! Попробуйте снова\n");
                    goto UI1;
                }

                if (row > 1000)
                {
                    printf("\nСлишком большая размерность! Попробуйте снова\n");
                    printf("TRY AGAIN\n\n");
                    goto UI1;
                }

                UI2:
                printf("Введите количество столбцов матрицы/строк вектор-столбца:");

                if (!scanf("%d", &col))
                {
                    printf("Некорректный ввод!\n");
                    break;
                }

                if (col <= 0)
                {
                    printf("\nРазмерность матрицы не может быть отрицательной! Попробуйте снова\n");
                    goto UI2;
                }

                if (col > 1000)
                {
                    printf("\nСлишком большая размерность! Попробуйте снова\n");
                    goto UI2;
                }

                //int* column_vector = NULL;
                int** matrix = NULL;
                int* vector_column = NULL;

                if (!create_matrix(&matrix, row, col))
                {
                    printf("Попробуйте снова\n");
                    goto UI2;
                }
                if (!create_column_vector(&vector_column, col))
                {
                    printf("Попробуйте снова\n");
                    goto UI2;
                }

                printf("\nВведите матрицу:\n");
                if (!input_matrix(matrix, row, col))
                {
                    printf("Запустите программу заново\n");
                    break;

                }

                printf("\nВведите вектор-столбце:\n");
                if (!input_vector_column(vector_column, col))
                {
                    printf("Запустите программу заново\n");
                    break;
                }
                new_menu(matrix, vector_column, row, col);

                delete_vector_column(&vector_column);
                delete_matrix(&matrix, row);
                goto UI;
            }
            else if (choice == 2)// Готов
            {
                int row = 0;
                int col = 0;

                printf("\nМаксимальная размерность матрицы 1000х1000!\n");

                UI3:
                printf("Введите количество строк матрицы: ");

                if (!scanf("%d", &row))
                {
                    printf("Некорректный ввод!\n");
                    break;
                }

                if (row <= 0)
                {
                    printf("\nРазмерность матрицы не может быть отрицательной! Попробуйте снова\n");
                    goto UI3;
                }

                if (row > 1000)
                {
                    printf("\nСлишком большая размерность! Попробуйте снова\n");
                    goto UI3;
                }

                UI4:
                printf("Введите количество столбцов матрицы/строк вектор-столбца:");

                if (!scanf("%d", &col))
                {
                    printf("Некорректный ввод!\n");
                    break;
                }

                if (col <= 0)
                {
                    printf("Размерность матрицы не может быть отрицательной! Попробуйте снова\n");
                    goto UI4;
                }

                if (col > 1000)
                {
                    printf("\nСлишком большая размерность! Попробуйте снова\n");
                    goto UI4;
                }

                int** matrix = NULL;
                int* VC = NULL;

                create_matrix(&matrix, row, col);
                create_column_vector(&VC, col);
                zero_fill_matrix(matrix, row, col);
                zero_fill_vector(VC, col);
                printf("\nВведите 1001 во время выбора строки чтобы остановиться\n\n");
                int new_row;
                int new_col;
                int elem;
                printf("\n\nВвод матрицы по координатам: \n");
                UI8:
                while (1)//Координатный ввод матрицы
                {
                    UI5:
                    printf("Введите строку элемента:");
                    scanf("%d", &new_row);
                    if (new_row == 1001)
                    {
                        printf("Конец ввода...\n");
                        break;
                    }

                    if ((new_row > row) || (new_row < 0))
                    {
                        printf("Некорректный ввод! Попробуйте снова\n");
                        goto UI5;
                    }
                    UI6:
                    printf("Введите столбец элемента:");
                    scanf("%d", &new_col);
                    if ((new_col > col) || (new_col < 0))
                    {
                        printf("Некорректный ввод! Попробуйте снова\n");
                        goto UI6;
                    }
                    printf("Введите значение элемента:");
                    scanf("%d", &elem);
                    matrix[new_row][new_col] = elem;

                    int zero_flag = 0;

                    for(int i = 0; i < row; i++)
                        for (int j = 0; j < col; j++)
                            if (matrix[i][j] == 0)
                                zero_flag = 1;
                    if (!zero_flag)
                    {
                        printf("\nМатрица полна!\n");
                        break;
                    }
                }

                if (!matrix_zero_checker(matrix, row, col))
                {
                    printf("\nМатрица пуста!\n");
                    goto UI8;
                }

                printf("\n\nВвод элемента вектор-столбца\n");
                UI9:
                while (1)//Координатный ввод вектор-столбца
                {
                    int new_row;
                    int elem;
                    UI7:
                    printf("Введите строку элемента вектор-столбца (1001 для окончания ввода):");
                    scanf("%d", &new_row);

                    if (new_row == 1001)
                    {
                        printf("Конец ввода\n");
                        break;
                    }
                    if ((new_row > row) || (new_row < 0))
                    {
                        printf("Некорректный ввод! Попробуйте снова\n");
                        goto UI7;
                    }
                    printf("Введите значение элемента вектор-столбца:");
                    scanf("%d", &elem);
                    VC[new_row] = elem;
                    int zero_flag = 0;
                    for(int i = 0; i < row; i++)
                        if (VC[i] == 0)
                            zero_flag = 1;

                    if (!zero_flag)
                    {
                        printf("Вектор-столбце полон!");
                        break;
                    }
                }

                if (!vector_zero_checker(VC, row))
                {
                    printf("\nВектор-столбце пуст!\n");
                    goto UI9;
                }
                new_menu(matrix, VC, row, col);
                //delete_matrix(&matrix, row);
                delete_vector_column(&VC);
                goto UI;

            }
            else if (choice == 3)//Готово
            {
                int row = 0;
                int col = 0;

                printf("\nМаксимальная размерность матрицы 1000х1000!\n");

                UI10:
                printf("Введите количество строк матрицы: ");

                if (!scanf("%d", &row))
                {
                    printf("Некорректный ввод!");
                    break;
                }

                if (row <= 0)
                {
                    printf("\nРазмерность матрицы не может быть отрицательной! Попробуйте снова\n");
                    goto UI10;
                }

                if (row > 1000)
                {
                    printf("\nСлишком большая размерность! Попробуйте снова\n");
                    goto UI10;
                }

                UI11:
                printf("Введите количество столбцов матрицы/строк вектор-столбца:");

                if (!scanf("%d", &col))
                {
                    printf("Некорректный ввод!\n");
                    break;
                }

                if (col <= 0)
                {
                    printf("\nРазмерность матрицы не может быть отрицательной! Попробуйте снова\n");
                    goto UI11;
                }

                if (col > 1000)
                {
                    printf("\nСлишком большая размерность! Попробуйте снова\n");
                    goto UI11;
                }

                int** matrix = NULL;
                int* VC = NULL;
                int procentage;
                int procentage1;

                create_matrix(&matrix, row, col);
                create_column_vector(&VC, col);

                printf("\nВведите процент разр. матрицы:");
                scanf("%d", &procentage);
                if (procentage < 0)
                {
                    printf("Отрицательный процент!\n");
                    return -1;
                }
                if (procentage > 100)
                {
                    printf("Слишком большой процент!\n");
                    return -1;
                }
                random_filling_matrix(matrix, row, col, procentage);

                printf("\nВведите процент разр. вектор-столбца:");
                scanf("%d", &procentage1);
                if (procentage1 < 0)
                {
                    printf("Отрицательный процент!\n");
                    return -1;
                }
                if (procentage > 100)
                {
                    printf("Слишколм большой процент!\n");
                    return -1;
                }
                random_filling_vector(VC, row, procentage);
                new_menu(matrix, VC, row, col);

                //delete_matrix(&matrix, row);
                delete_vector_column(&VC);
                goto UI;
            }
            else if (choice == 0)//Готов
            {
                printf("Выход...\n");
                break;
            }

        }
    return 1;
}
