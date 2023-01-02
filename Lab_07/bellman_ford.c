#include "app.h"

void BellmanFord(int **graph, int V, int E, int src, int a)
{
    //Инцилизация расстояний всех вершин как INF.
    int dis[V];
    for (int i = 0; i < V; i++)
        dis[i] = INF;

    //Инцилизация расстояния источника как 0
    dis[src] = 0;

    //Релаксация всех ребер |V| - 1 раз
    for (int i = 0; i < V - 1; i++)
    {
        for(int j = 0; j < E; j++)
        {
            if (dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
                dis[graph[j][1]] =  dis[graph[j][0]] + graph[j][2];
        }
    }

    //Проверка на негативный цикл.
    for (int i = 0; i < E; i++)
    {
        int x = graph[i][0];
        int y = graph[i][1];
        int weight = graph[i][2];
        if (dis[x] != INF && dis[x] + weight < dis[y])
        {
            puts("Граф содержит цикл с негативным весом");
            return;
        }
    }

    //Печать расстояний
    int flag = 0;
    for (int i = 0; i < V; i++)
    {
        if (dis[i] <= a && i != src)
        {
            flag++;
            if (flag==1)
                puts("Вершина | Расстояние от источника");
            printf("%7d | %d\n", i, dis[i]);
        }
    }

    if (!flag)
        puts("Таких вершин нет!");
}

//Для времени работы алгоритма
void BellmanFord_time(int **graph, int V, int E, int src, int a)
{
    int dis[V];
    for(int i = 0; i < V; i++)
        dis[i] = INF;

    dis[src] = 0;
    for (int i = 0; i < V - 1; i++)
    {
        for(int j = 0; j < E; j++)
        {
            if (dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
                dis[graph[j][1]] =  dis[graph[j][0]] + graph[j][2];
        }
    }

    for (int i = 0; i < E; i++)
    {
        int x = graph[i][0];
        int y = graph[i][1];
        int weight = graph[i][2];
        if (dis[x] != INF && dis[x] + weight < dis[y])
        {
            puts("Граф содержит цикл с негативным весом");
            return;
        }
    }
}
