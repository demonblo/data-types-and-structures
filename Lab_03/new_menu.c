#include "head.h"

void new_menu(int** a, int* VC, int row, int col)
{
    int choice;
    int* b = NULL;
    sparse_vector sparse_vector_result;
    sparse_matrix sparse_matrix;
    sparse_vector sparse_vector;


    UI:
    printf("\nMENU:\n");
    printf("1) Распечатать матрицу в 'классическом' виде\n");
    printf("2) Распечатать вектор-столбец в 'классическом' виде\n");
    printf("3) Распечатать матрицу в разреженом формате\n");
    printf("4) Распечатать вектор-столбец в разреженом формате\n");
    printf("5) Распечатать результат перемножения в 'классическом' виде\n");
    printf("6) Распечатать результат перемножения разреженым алгоритмом в разреженом формате\n");
    printf("7) Сравнить классический и разреженный методы\n");
    printf("0) Выход\n");
    if (!scanf("%d", &choice))
    {
        printf("\nНекорректный ввод!\n");
        return;
    }

    if ((choice > 7) || (choice < 0))
    {
        printf("Такого пункта нет в меню, попробуйте еще!\n");
        goto UI;
    }
    if (choice == 0)//Готов
    {
        return;
    }
    else if (choice == 1)//Готов
    {
        printf("\n");
        printf("Матрица: \n");
        output_matrix(a, row, col);
    }
    else if (choice == 2)//Готов
    {
        printf("\n");
        printf("Вектор-столбец:\n");
        output_VC(VC, col);
        printf("\n");
        printf("\n");
    }
    else if (choice == 3)//Готов
    {
        sparse_creator(a, row, col, &sparse_matrix);
        sparse_input(a, row, col, sparse_matrix);
        printf("\n Матрица в разреженом виде: \n");
        sparse_output(sparse_matrix);
        sparse_delete(&sparse_matrix);

    }
    else if (choice == 4)//Готов
    {
        printf("Вектор-столбец в разреженом виде: \n");
        create_sparse_VC(&sparse_vector, VC, col);
        input_sparse_VC(sparse_vector, VC, col);
        output_sparse_vector(sparse_vector);
        delete_sparse_vector(&sparse_vector);
    }
    else if (choice == 5)//Готов
    {
        create_column_vector(&b, col);
        multiplication(a, VC, b, row, col);
        printf("\nРезультат перемножения в классическом формате: \n");
        output_VC(b, row);
        delete_vector_column(&b);
    }
    else if (choice == 6)//Готов
    {
        sparse_creator(a, row, col, &sparse_matrix);
        sparse_input(a, row, col, sparse_matrix);

        printf("\nРезультат перемножения разреженым алгоритмом в разреженом формате: \n");
        create_sparse_VC(&sparse_vector, VC, col);
        input_sparse_VC(sparse_vector, VC, col);

        create_column_vector(&b, row);
        for (int i = 0; i < row; i++)
            b[i] = 0;
        sparse_multiplication(sparse_matrix, sparse_vector, b);

        create_sparse_VC(&sparse_vector_result, b, row);
        input_sparse_VC(sparse_vector_result, b, row);

        output_sparse_vector(sparse_vector_result);

        delete_sparse_vector(&sparse_vector);
        delete_sparse_vector(&sparse_vector_result);
        sparse_delete(&sparse_matrix);
        delete_vector_column(&b);
    }
    else if (choice == 7)
    {
        int row_time = 500;
        int col_time = 500;
        int** a1;
        int* vector;
        double time_result_sparse;
        clock_t start_sparse;
        clock_t end_sparse;
        double time_result_classic;
        clock_t start_classic;
        clock_t end_classic;
        long int sparse_mem;
        long int classic_mem;

        int row_time_spec = 50;
        int col_time_spec = 50;

        printf("|                              %4d *%4d                        |\n", row_time_spec, col_time_spec);
        printf("|Процент| Разр. время | Класc. время | Разр. пам. | Класс. пам.  |\n");
        for (int procentage = 0; procentage <= 100; procentage += 20)
        {
            create_matrix(&a1, row_time_spec, col_time_spec);
            create_column_vector(&vector, row_time_spec);

            random_filling_matrix(a1, row_time_spec, col_time_spec, procentage);
            random_filling_vector(vector, row_time_spec, procentage);

            create_sparse_VC(&sparse_vector, vector, row_time_spec);
            input_sparse_VC(sparse_vector, vector, row_time_spec);

            sparse_creator(a1, row_time_spec, col_time_spec, &sparse_matrix);
            sparse_input(a1, row_time_spec, col_time_spec, sparse_matrix);

            create_column_vector(&b, row_time_spec);

            start_sparse = clock();
            sparse_multiplication(sparse_matrix, sparse_vector, b);
            if (procentage == 100)
                vector_zero_filling(b, row_time_spec);
            end_sparse = clock();
            sparse_mem = (3 * non_zero_counter(a1, row_time_spec, col_time_spec) * sizeof(int)) + (3 * non_zero_counter_VC(vector, row_time_spec) * sizeof(int)) + (3 * non_zero_counter_VC(b, row_time_spec) * sizeof(int));

            start_classic = clock();
            multiplication(a1, vector, b, row_time_spec, col_time_spec);
            if (procentage == 100)
                vector_zero_filling(b, row_time_spec);
            end_classic = clock();
            classic_mem = sizeof(**a1) * row_time_spec * col_time_spec + sizeof(*b) * 2 * row_time_spec + sizeof(*vector) * 2 * row_time_spec;
            //delete_matrix(&matrix, row);
            delete_vector_column(&vector);
            time_result_classic = end_classic - start_classic;
            time_result_sparse = (end_sparse - start_sparse);
            printf("| %6d|%13lf|%13lf |%12ld|%12ld  |\n", procentage, (time_result_sparse) * (3) / 1000, time_result_classic / 1000, sparse_mem, classic_mem);
        }

        ///////////////
        for (;row_time <= 1000; row_time += 100, col_time += 100)
        {
            printf("|                              %4d *%4d                        |\n", row_time, col_time);
            printf("|Процент| Разр. время | Класc. время | Разр. пам. | Класс. пам.  |\n");
            for (int procentage = 0; procentage <= 100; procentage += 20)
            {
                create_matrix(&a1, row_time, col_time);
                create_column_vector(&vector, row_time);

                random_filling_matrix(a1, row_time, col_time, procentage);
                random_filling_vector(vector, row_time, procentage);

                create_sparse_VC(&sparse_vector, vector, row_time);
                input_sparse_VC(sparse_vector, vector, row_time);

                sparse_creator(a1, row_time, col_time, &sparse_matrix);
                sparse_input(a1, row_time, col_time, sparse_matrix);

                create_column_vector(&b, row_time);

                start_sparse = clock();
                sparse_multiplication(sparse_matrix, sparse_vector, b);
                if (procentage == 100)
                    vector_zero_filling(b, row_time);
                end_sparse = clock();
                sparse_mem = (3 * non_zero_counter(a1, row_time, col_time) * sizeof(int)) + (3 * non_zero_counter_VC(vector, row_time) * sizeof(int)) + (3 * non_zero_counter_VC(b, row_time) * sizeof(int));

                start_classic = clock();
                multiplication(a1, vector, b, row_time, col_time);
                if (procentage == 100)
                    vector_zero_filling(b, row_time);
                end_classic = clock();
                classic_mem = sizeof(**a1) * row_time * col_time + sizeof(*b) * 2 * row_time + sizeof(*vector) * 2 * row_time;
                //delete_matrix(&matrix, row);
                delete_vector_column(&vector);
                time_result_classic = end_classic - start_classic;
                time_result_sparse = (end_sparse - start_sparse);
                printf("| %6d|%13lf|%13lf |%12ld|%12ld  |\n", procentage, (time_result_sparse) * (3) / 1000, time_result_classic / 1000, sparse_mem, classic_mem);
            }
        }
    }
    goto UI;
}
