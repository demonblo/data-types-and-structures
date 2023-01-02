#include "app.h"

void free_matrix(int **mtr, int E)
{
    for (int i = 0; i < E; i++)
        if (mtr[i])
            free(mtr[i]);
    free(mtr);
}

int **create_matrix(int E)
{
    int **mtr = (int**)calloc(E, sizeof(int*));
    if (!mtr)
        return NULL;
    for (int i = 0; i < E; i++)
    {
        mtr[i] = (int*)calloc(3, sizeof(int));
        if (!mtr[i])
        {
            free_matrix(mtr, E);
            return NULL;
        }
    }
    return mtr;
}
