#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR             -1
#define CAPACITY_OF_EXIT       0.8
#define MAX_LENGTH_OF_WAIT       6
#define MAX_LENGTH_OF_PROCESSING 1

typedef struct element_of_queue_array_s
{
    double time_for_processing;
    double output_capacity;
} element_of_queue_array_t;

typedef struct element_of_queue_list_s
{
    double time_for_processing;
    double output_capacity;
    struct element_of_queue_s* next;
} element_of_queue_list_t;

typedef struct queue_s
{
    element_of_queue_list_t *head;
    int length;
} queue_t;

double random_double(int max)
{
    double num = (double)(rand() % (1000 * max)) / 1000;

    return num;
}

int main()
{
    queue_t *queue;
    //element_of_queue_list_t *pointer_for_list;
    //element_of_queue_array_t array[1000];
    element_of_queue_list_t *pointer = NULL;
    int counts_of_outs = 0;
    double length_of_wait = 0;

    queue = (queue_t*)malloc(sizeof (queue_t));
    queue->head = NULL;
    queue->length = 0;
    while (counts_of_outs < 1000)
    {
        if (length_of_wait <= 0)
        {
            pointer = (element_of_queue_list_t*)malloc(sizeof (element_of_queue_list_t));
            pointer->output_capacity = random_double(1);
            pointer->time_for_processing = random_double(1);
            queue->head = pointer;
        }
        if (queue->head->time_for_processing <= 0.0 && queue->head != NULL)
        {
            if (queue->head->output_capacity > 0.8)
            {
                free(queue->head);
                queue->head = NULL;
                counts_of_outs++;
                printf("молодец\n");
            }
            else
            {
                queue->head->output_capacity = random_double(1);
                printf("даун\n");
            }
        }
        else
            queue->head->time_for_processing -= 1.0;
        if (length_of_wait <= 0.0)
            length_of_wait = random_double(6);
        else
            length_of_wait -= 1.0;
    }

    return 0;
}
