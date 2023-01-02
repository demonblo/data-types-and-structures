#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#endif // HEAD_H

typedef struct
{
    int* JA;
    int* AN;
    int* IP;
    int cnt_JA;
    int cnt_AN;
    int cnt_IP;

} sparse_matrix;

typedef struct
{
    int* JA;
    int* AN;
    int* IP;
    int cnt;
} sparse_vector;
int create_matrix(int*** a, int row, int col);

int create_column_vector(int **a, int row);

void delete_matrix(int*** a, int row);

void delete_vector_column(int** vector_column);

int input_matrix(int** a, int row, int col);

int input_vector_column(int* vector_column, int row);

void output_matrix(int** a, int row, int col);

void output_VC(int* a, int row);

void new_menu(int** a, int* VC, int row, int col);

void multiplication(int** a, int* VC, int* b, int row, int col);

void zero_fill_matrix(int** matrix, int row, int col);

void zero_fill_vector(int* VC, int row);

int matrix_zero_checker(int** a, int row, int col);

int vector_zero_checker(int* a, int row);

void random_filling_matrix(int** a, int row, int col, int procentage);

void random_filling_vector(int* a, int row, int procentage);

void sparse_creator(int** a, int row, int col, sparse_matrix *matrix);

int non_zero_counter(int** a, int row, int col);

void sparse_input(int** a, int row, int col, sparse_matrix matrix);

void sparse_output(sparse_matrix matrix);

void sparse_delete(sparse_matrix *matrix);

void create_sparse_VC(sparse_vector *vector, int* a, int row);

void input_sparse_VC(sparse_vector vector, int* a, int row);

void output_sparse_vector(sparse_vector vector);

void delete_sparse_vector(sparse_vector *vector);

int non_zero_counter_VC(int* a, int row);

void sparse_multiplication(sparse_matrix matrix, sparse_vector vector, int* a);

void vector_zero_filling(int* a, int row);
