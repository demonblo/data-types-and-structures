#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 100000
int **create_matrix(int E); //Создание матрицы
void free_matrix(int **mtr, int E); //Очищение память
void show_matr_gv(int **a, int E); //Распечатка графа
void BellmanFord(int **graph, int V, int E, int src, int a); //Алгоритм Белмана-Форда
void BellmanFord_time(int **graph, int V, int E, int src, int a); //Засечение времени
#endif // APP_H
