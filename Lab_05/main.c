#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CHANCE_TO_SAVE       0.8
#define MAX_WAIT_TIME          6
#define MAX_PROCESS_TIME       1
#define MAX_ELEMENTS        1000
#define EPS                 1E-6
#define STEP                 100


typedef struct node
{
    double wait_time;
    double prcs_time;
    double chance;
    struct node *next;
} node_t;

typedef struct
{
    size_t size;
    node_t *head;
    node_t *tail;
} queue_t;

typedef struct
{
    double all_time;
    double stay_time;
    size_t average_length;
    size_t elements_in;
    size_t elements_out;
    size_t calls_number;
    bool address_flag;
} process_t;

typedef struct
{
    double wait_time;
    double prcs_time;
    double chance;
} array_elem;

typedef struct
{
    array_elem arr[MAX_ELEMENTS];
    int head;
    int tail;
} array_t;


double create_rand(int max_digit)
{
    double rand_result = (double)(rand() % (MAX_ELEMENTS * max_digit)) / MAX_ELEMENTS;
    return rand_result;
}

unsigned long long tick(void)
{
  unsigned long long d;
  __asm__ __volatile__("rdtsc" : "=A"(d));
  return d;
}

void add_elemet_queue(queue_t *temp, node_t *new)
{
    if (temp->size == 0)
        temp->head = new;
    else
        temp->tail->next = new;

    temp->tail = new;
    temp->size++;
}

void free_queue(queue_t *temp)
{
    for (node_t *cur = temp->head; temp->head; temp->head = cur)
    {
        cur = temp->head->next;
        free(temp->head);
    }
    temp->head = NULL;
    temp->tail = NULL;
    temp->size = 0;
}

node_t *create_node(void)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL)
        return NULL;
    new_node->wait_time = create_rand(MAX_WAIT_TIME);
    new_node->prcs_time = create_rand(MAX_PROCESS_TIME);
    new_node->chance = create_rand(1);
    new_node->next = NULL;
    return new_node;
}

int pop_elemnt_queue(queue_t *temp)
{
    if (temp->head == NULL)
        return EXIT_FAILURE;

    node_t *new_head = temp->head->next;
    free(temp->head);
    temp->head = new_head;
    temp->size--;
    return EXIT_SUCCESS;
}

void main_process_list(queue_t *queue, process_t *main_struct)
{
    double proc_time = 0.0;
    node_t *pntr = NULL;
    node_t *new_node = create_node();
    if (new_node == NULL)
        return;
    if (main_struct->address_flag)
        printf("Добавлен элемент:   %p\n", (void*)new_node);
    if (queue->head && new_node->wait_time < queue->head->prcs_time)
    {
        main_struct->all_time += queue->head->prcs_time;
        main_struct->average_length += queue->size;
        main_struct->elements_in++;
        add_elemet_queue(queue, new_node);
        if (queue->head->chance > CHANCE_TO_SAVE + EPS)
        {
            if (main_struct->address_flag)
                printf("Удалён элемент: %p\n", (void*)queue->head);
            pop_elemnt_queue(queue);
            main_struct->elements_out++;
        }
        else
        {
            queue->head->chance = create_rand(1);
            pntr = queue->head;
            queue->head = queue->head->next;
            pntr->next = NULL;
            add_elemet_queue(queue, pntr);
            queue->size--;
        }
        if (++main_struct->calls_number % STEP == 0)
        {
            printf("\n-------------------------------\n");
            printf("Заявок обслужано: %zu\n", main_struct->calls_number);
            printf("Длина очереди = %zu\n", queue->size);
            printf("Средняя длина очереди = %zu\n", main_struct->average_length / STEP);
            printf("-------------------------------\n\n");
            main_struct->average_length = 0;
        }
        return;
    }
    while (queue->size != 0 && proc_time < new_node->wait_time - EPS)
    {
        if (main_struct->elements_out == MAX_ELEMENTS)
        {
            free(new_node);
            return;
        }
        proc_time += queue->head->prcs_time;
        main_struct->all_time += queue->head->prcs_time;
        main_struct->average_length += queue->size;
        if (queue->head->chance > CHANCE_TO_SAVE + EPS)
        {
            if (main_struct->address_flag)
                printf("Удалён элемент: %p\n", (void*)queue->head);
            pop_elemnt_queue(queue);
            main_struct->elements_out++;
        }
        else if (queue->head->next)
        {
            pntr = queue->head;
            queue->head = queue->head->next;
            pntr->chance = create_rand(1);
            pntr->next = NULL;
            add_elemet_queue(queue, pntr);
            queue->size--;
        }
        else
        {
            queue->head->chance = create_rand(1);
        }
        if (++main_struct->calls_number % STEP == 0)
        {
            printf("\n-------------------------------\n");
            printf("Обслужано заявок: %zu\n", main_struct->calls_number);
            printf("Длина очереди = %zu\n", queue->size);
            printf("Средняя длина очереди = %zu\n", main_struct->average_length / STEP);
            printf("-------------------------------\n\n");
            main_struct->average_length = 0;
        }
    }
    if (proc_time < new_node->wait_time - EPS)
    {
        main_struct->all_time += new_node->wait_time - proc_time;
        main_struct->stay_time += new_node->wait_time - proc_time;
    }
    add_elemet_queue(queue, new_node);
    main_struct->elements_in++;
}

void main_process_array(array_t *temp, process_t *main_struct)
{
    double proc_time = 0.0;
    bool key = false;
    array_elem new_element;
    new_element.wait_time = create_rand(MAX_WAIT_TIME);
    new_element.prcs_time = create_rand(MAX_PROCESS_TIME);
    new_element.chance = create_rand(1);
    while (temp->head != temp->tail + MAX_ELEMENTS * key && proc_time < new_element.wait_time - EPS)
    {
        if ((temp->head %= MAX_ELEMENTS) == 0 && key)
            key = false;
        if ((temp->tail %= MAX_ELEMENTS) == 0)
            key = true;
        if (main_struct->elements_out == MAX_ELEMENTS)
            return;

        proc_time += temp->arr[temp->head].prcs_time;
        main_struct->all_time += temp->arr[temp->head].prcs_time;
        if (temp->arr[temp->head].chance > CHANCE_TO_SAVE + EPS)
        {
            temp->head++;
            main_struct->elements_out++;
        }
        else
        {
            temp->arr[temp->head].chance = create_rand(1);
            main_struct->elements_in++;
        }
    }
    if (proc_time < new_element.wait_time - EPS)
    {
        main_struct->all_time += new_element.wait_time - proc_time;
        main_struct->stay_time += new_element.wait_time - proc_time;
    }
    temp->arr[temp->tail++] = new_element;
    main_struct->elements_in++;
}

void analyse_information( unsigned long long que, unsigned long long arr)
{
    int sizes[6] = {10, 50, 100, 300, 500, 1000};
    printf("ИНформация для анализа:\n\n");
    printf("Размер очереди для 1000 элементов: от %zu B до %zu B\n", sizeof(node_t) + 2 * sizeof(node_t*), sizeof(node_t) * MAX_ELEMENTS + 2 * sizeof(node_t*));
    printf("---------------------------------------------------------\n");
    printf("Время для списка в тиках: %llu\n", que);
    printf("\n\nВремя для массива в тиках: %llu\n", arr);
    printf("Размер массива |");
    for (int i = 0; i < 6; i++)
        printf("%6d|", sizes[i]);
    printf("\n---------------------------------------------------------\n");
    printf("Память(B)     |");
    for (int i = 0; i < 6; i++)
        printf("%6zu|", (sizeof(array_elem) * sizes[i]) + (2 * sizeof(int)));
    printf("\n\n");
}

void final_output(process_t *temp, size_t size)
{
    printf("\n\n-------Вывод-------\n");
    printf("Общее время = %.5lf\n", temp->all_time);
    printf("Время простоя = %.5lf\n", temp->stay_time);
    printf("Элементов вошло = %zu\n", temp->elements_in);
    printf("Элементов вышло = %zu\n", temp->elements_out);
    printf("Элементов очсталось в очереди = %zu\n", size);
    printf("Среднее время в очереди = %.5lf\n", (temp->all_time + temp->stay_time / 2) / temp->elements_in);
    printf("Вызовов аппарата = %zu\n", temp->calls_number);
    printf("-------------------------------\n\n");
}

int input_bool(char *string)
{
    char ch;
    printf("%s", string);
    while ((ch = getc(stdin)) != 'y' && ch != 'n')
    {
        while ((ch = getc(stdin)) != '\n' && ch != EOF);
        printf("Некорректный ввод, попробуйте снова!\n%s", string);
    }
    if (ch == 'n')
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int main(void)
{
    srand(time(NULL));
    queue_t queue = {0, NULL, NULL};
    array_t arr;
    arr.head = 0;
    arr.tail = 0;
    process_t main_struct = {0.0, 0.0, 0, 0, 0, 0, false};
    if (input_bool("Показывать адреса?(y|n):") == EXIT_SUCCESS)
        main_struct.address_flag = true;
    unsigned long long begin = tick();
    while (main_struct.elements_out != MAX_ELEMENTS)
        main_process_list(&queue, &main_struct);
    unsigned long long end = tick();
    unsigned long long queue_time = end - begin;
    final_output(&main_struct, queue.size);
    process_t arr_struct = {0.0, 0.0, 0, 0, 0, 0, false};
    begin = tick();
    while (arr_struct.elements_out != MAX_ELEMENTS)
        main_process_array(&arr, &arr_struct);

    end = tick();
    analyse_information(queue_time, (end - begin));
    free_queue(&queue);

}
