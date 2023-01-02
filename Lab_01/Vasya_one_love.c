#include <stdio.h>
#include <math.h>

struct car_t
{
    char name[16];
    int cost;
    int distance;
};


void input_car(struct car_t *a)
{
    scanf("%s", (*a).name);
    scanf("%d", &(*a).cost);
    scanf("%d", &(*a).distance);
}


void compare_cost(struct car_t a, int *max)
{
    if (a.cost > (*max))
        *max = a.cost;
}

void compare_distance(struct car_t a, int *max)
{
    if (a.distance > (*max))
        *max = a.distance;
}

int find_max(struct car_t a[3], void(*find)(struct car_t , int*))
{
    int max = 0;
    for (int i = 0; i < 3; i++)
    {
        find(a[i], &max);
    }

    return max;
}

int main()
{
    struct car_t cars[3];

    for (int i = 0; i < 3; i++)
        input_car(&cars[i]);

    printf("%d\n", find_max(cars, compare_cost));



    return 0;
}
