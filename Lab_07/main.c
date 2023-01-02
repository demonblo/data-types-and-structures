#include "app.h"

void print_interface(void)
{
    puts("******************************");
    puts("*************МЕНЮ*************");
    puts("1: Распечатать граф");
    puts("2: Найти путь");
    puts("0: Выход");
    printf("Ваш выбор: ");
}

int main()
{
    int V;
    int E;
    FILE *f = fopen("graph.txt", "r");
    //FILE *f = fopen("graph_negative.txt", "r");
    if (!f)
    {
         printf("Некорректный ввод!");
         return EXIT_FAILURE;
    }
    puts("Найти все вершины графа, к которым от заданной вершины можно добраться по пути не длиннее А.");
    if (fscanf(f, "%d %d", &V, &E)!=2)
    {
        puts("Неверные данные!\n");
        return EXIT_FAILURE;
    }
    int **mtr=create_matrix(E);
    int u,v,w;
    for (int i = 0; i < E; i++)
    {
        if (fscanf(f,"%d %d %d",&u,&v,&w)!=3 || (u>V) || (u<0) || (v>V) || (v<0))
        {

            puts("Неверные данные!\n");
            free_matrix(mtr,E);
            return EXIT_FAILURE;
        }
        mtr[i][0]=u;
        mtr[i][1]=v;
        mtr[i][2]=w;
    }
    fclose(f);
    int choice;
    while (1)
    {
        print_interface();
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
            case 0:
                return EXIT_SUCCESS;
            case 1:
            {
                show_matr_gv(mtr, E);
                break;
            }
            case 2:
            {
                int src;
                int a;
                printf("Введите вершину: ");
                if (scanf("%d",&src)!=1 || (src > V) || (src < 0))
                {
                    puts("Неверная вершина!\n");
                    break;
                }
                printf("Введите путь: ");
                if (scanf("%d",&a)!=1)
                {
                    puts("Неверный путь!\n");
                    break;
                }
                BellmanFord(mtr, V, E, src, a);
               /* time_t start,end;
                start=clock();
                for (int i=0; i<1000000; i++)
                    BellmanFord_time(mtr, V, E, src, a);
                end=clock();
                double time_res= ((double)(end - start) / CLOCKS_PER_SEC);
                printf("Use memory: %I64d bytes\n", E*3*sizeof(int));
                printf("Time work: %.6lfE-6\n", time_res);*/
            }
        }
    }
}
