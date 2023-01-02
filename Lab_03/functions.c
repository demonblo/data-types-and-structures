#include "head.h"

void multiplication(int** a, int* VC, int* b, int row, int col)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            b[i] = 0;
            for (int k = 0; k < col; k++)
                b[i] += a[i][k] * VC[k];
        }
}

int matrix_zero_checker(int** a, int row, int col)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (a[i][j] != 0)
                return 1;

    return 0;
}

int vector_zero_checker(int* a, int row)
{
    for (int i = 0; i < row; i++)
        if (a[i] != 0)
            return 1;

    return 0;
}

void zero_fill_matrix(int** matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = 0;
}

void zero_fill_vector(int* VC, int row)
{
    for (int i = 0; i < row; i++)
        VC[i] = 0;
}

void random_filling_matrix(int** a, int row, int col, int procentage)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            if((0 + rand() % (101 - 0)) > procentage)
                a[i][j] = (0 + rand() % (10 - 0));
            else
                a[i][j] = 0;
        }
}

void random_filling_vector(int* a, int row, int procentage)
{
    for (int j = 0; j < row; j++)
    {
        if((0 + rand() % (101 - 0)) > procentage)
            a[j] = (0 + rand() % (10 - 0));
        else
            a[j] = 0;
    }
}

int non_zero_counter(int** a, int row, int col)
{
    int counter = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (a[i][j] != 0)
                counter++;

    return counter;
}

int non_zero_counter_VC(int* a, int row)
{
    int counter = 0;
    for (int i = 0; i < row; i++)
        if (a[i] != 0)
            counter++;

    return counter;
}

void sparse_multiplication(sparse_matrix matrix, sparse_vector vector, int* a)
{
    for (int i = 0; i < matrix.cnt_JA; i++)
    {
        for (int j = 0; j < vector.cnt; j++)
            if (matrix.JA[i] == vector.JA[j])
                a[matrix.IP[i]] += vector.AN[j] * matrix.AN[i];
    }
}

void vector_zero_filling(int* a, int row)
{
    for (int i = 0; i < row; i++)
        a[i] = 0;
}
