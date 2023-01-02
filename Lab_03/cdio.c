#include "head.h"

int create_matrix(int*** a, int row, int col)
{
    *a = (int**)malloc(row * sizeof(int*));

    if (*a == NULL)
    {
        printf("Ошибка!");
        return 0;
    }
    for (int i = 0; i < row; i++)
    {
        *(*a + i) = NULL;
        *(*a + i) = (int*)malloc(col * sizeof(int));
        if (*(*a + i) == NULL)
        {
            printf("Ошибка!");
            return 0;
        }
    }
    return 1;
}

int create_column_vector(int** a, int row)
{
    *a = (int*)malloc(row * sizeof(int));
    if (*a == NULL)
    {
        printf("Ошибка!");
        return 0;
    }
    return 1;
}

void delete_matrix(int*** a, int row)
{
    for (int i = 0; i < row; i++)
        free(*a[i]);
    free(*a);
    //**a = NULL;
}

void delete_vector_column(int** a)
{
    free(*a);
    *a = NULL;
}

int input_matrix(int** a, int row, int col)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            printf("a[%d][%d] = ", i, j);
            if (!scanf("%d", &a[i][j]))
            {
                printf("Некорректный ввод!");
                return 0;
            }
        }
    return 1;
}

int input_vector_column(int* a, int row)
{
    for (int j = 0; j < row; j++)
    {
        printf("VC[%d] = ", j);
        if (!scanf("%d", &a[j]))
        {
            printf("Некорректный ввод!");
            return 0;
        }
    }
    return 1;

}

void output_matrix(int** a, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%3d", a[i][j]);
        printf("\n");
    }
}

void output_VC(int* a, int row)
{
    for (int i = 0; i < row; i++)
        printf("%6d\n", a[i]);
}

void sparse_output(sparse_matrix matrix)
{
    printf("|  JA  |");
    for (int i = 0; i < matrix.cnt_JA; i++)
        printf("%2d|", matrix.JA[i]);
    printf("\n");
    printf("|  AN  |");
    for (int i = 0; i < matrix.cnt_JA; i++)
        printf("%2d|", matrix.AN[i]);
    printf("\n");
    printf("|  IP  |");
    for (int i = 0; i < matrix.cnt_JA; i++)
        printf("%2d|", matrix.IP[i]);
    printf("\n");

}

void sparse_creator(int** a, int row, int col, sparse_matrix *matrix)
{
    int size = non_zero_counter(a, row, col);
    matrix->JA = (int*)malloc(size * sizeof(int));
    matrix->AN = (int*)malloc(size * sizeof(int));
    matrix->IP = (int*)malloc(size * sizeof(int));
    matrix->cnt_JA = size;
    matrix->cnt_AN = size;
    matrix->cnt_IP = size;
}

void sparse_input(int** a, int row, int col, sparse_matrix matrix)
{
    int counter = 0;

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (a[i][j] != 0)
            {
                matrix.JA[counter] = j;
                matrix.AN[counter] = a[i][j];
                matrix.IP[counter] = i;
                counter++;
            }

}

void sparse_delete(sparse_matrix *matrix)
{
    free(matrix->JA);
    free(matrix->AN);
    free(matrix->IP);
}

void create_sparse_VC(sparse_vector *vector, int* a, int row)
{
    int size = non_zero_counter_VC(a, row);

    vector->JA = (int*)malloc(size * sizeof(int));
    vector->AN = (int*)malloc(size * sizeof(int));
    vector->IP = (int*)malloc(size * sizeof(int));
    vector->cnt = size;
    for (int i = 0; i < size; i++)
        vector->IP[i] = 0;
}

void input_sparse_VC(sparse_vector vector, int* a, int row)
{
    int counter = 0;
    for (int i = 0; i < row; i++)
        if (a[i] != 0)
        {
            vector.JA[counter] = i;
            vector.AN[counter] = a[i];
            counter++;
        }
}

void output_sparse_vector(sparse_vector vector)
{
    printf("|  JA  |");
    for (int i = 0; i < vector.cnt; i++)
        printf("%4d|", vector.JA[i]);
    printf("\n");
    printf("|  AN  |");
    for (int i = 0; i < vector.cnt; i++)
        printf("%4d|", vector.AN[i]);
    printf("\n");
    printf("|  IP  |");
    for (int i = 0; i < vector.cnt; i++)
        printf("%4d|", vector.IP[i]);
    printf("\n");
}

void delete_sparse_vector(sparse_vector *vector)
{
    free(vector->JA);
    free(vector->AN);
    free(vector->IP);
}

