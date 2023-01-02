#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define true 1

typedef struct node
{
    int field;
    struct node *left;
    struct node *right;
}node_struct;

typedef struct node_h
{
    int value;
    struct node_h *next;
}  node_struct_hash;

long int tic(void)
{
    unsigned long long tmp;
    __asm__ __volatile__ ("rdtsc" : "=A" (tmp));
    return tmp;
}

node_struct *rotateright(node_struct *p)
{
    node_struct *q = p->left;
    p->left = q->right;
    q->right = p;
    return q;
}

node_struct *rotateleft(node_struct *q)
{
    node_struct* p = q->right;
    q->right = p->left;
    p->left = q;
    return p;
}

int bfactor(node_struct *head)
{
    if(head == NULL)
        return 0;
    int left, right;
    if (head->left != NULL)
    {
        left = bfactor(head->left);
    }
    else
        left = 0;
    if (head->right != NULL)
    {
        right = bfactor(head->right);
    }
    else
        right = 0;
    int max = left > right ? left : right;
    return max + 1;
}

node_struct *balance(node_struct *p)
{
    if((bfactor(p->right) - bfactor(p->left))== 2)
    {
        if((bfactor(p->right->right) - bfactor(p->right->left)) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if((bfactor(p->right) - bfactor(p->left))==-2)
    {
        if((bfactor(p->left->right) - bfactor(p->left->left)) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

node_struct *add_node(node_struct *head, node_struct *new_node, int type)
{
    if (head == NULL)
    {
        return new_node;
    }
    else
    {
        if (head->field >= new_node->field)
        {
            head->left = add_node(head->left, new_node, type);
        }
        else
        {
            head->right = add_node(head->right, new_node, type);
        }
    }
    if(type)
        return balance(head);
    else
        return head;
}

node_struct *create_node(int elem)
{
    node_struct *temp;
    temp = (node_struct*)malloc(sizeof(node_struct));
    temp->field = elem;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void walk_req(node_struct *head, FILE *file, node_struct *pointer)
{
    if (head == pointer && pointer != NULL)
    {
        fprintf(file, "%d [fillcolor=red, style=filled];\n", head->field);
    }
    else
        fprintf(file, "%d;\n", head->field);
    if (head->left)
    {
        fprintf(file, "%d -- %d;\n", head->field, head->left->field);
        walk_req(head->left, file, pointer);
    }
    if(head->right)
    {
        fprintf(file, "%d -- %d;\n", head->field, head->right->field);
        walk_req(head->right, file, pointer);
    }
}

void walk_tree(node_struct *head, node_struct *pointer)
{
    FILE *file = fopen("input.dot", "w");
    fprintf(file, "graph \"\"\n");
    fprintf(file, "{\n");
    walk_req(head, file, pointer);
    fprintf(file, "}\n");
    fclose(file);
    system("dot -Tpng input.dot -o output.png");
    system("open -a Preview output.png");
}

void inorder(node_struct *p)
{
    if (p != NULL)
    {
        inorder(p->left);
        printf("%d ",p->field);
        inorder(p->right);
    }
}

void preorder(node_struct *p)
{
    if (p != NULL)
    {
        printf("%d ",p->field);
        preorder(p->left);
        preorder(p->right);
    }
}

void postorder(node_struct *p)
{
    if (p != NULL)
    {
        postorder(p->left);
        postorder(p->right);
        printf("%d ",p->field);
    }
}

void free_tree(node_struct *head)
{
    if (head->left)
    {
        free_tree(head->left);
    }
    if (head->right)
    {
        free_tree(head->right);
    }
    free(head);
}

void print_tree(void)
{
    FILE *file = fopen("val.txt", "r");
    node_struct *head = NULL;

    int value;

    while(fscanf(file, "%d", &value) == 1)
        head = add_node(head, create_node(value), 0);

    walk_tree(head, NULL);
    fclose(file);
    printf("Infix :");
    inorder(head);
    printf("\n------------------------------\n");
    printf("Prefix :");
    preorder(head);
    printf("\n------------------------------\n");
    printf("Postfix :");
    postorder(head);
    printf("\n------------------------------\n");
    free_tree(head);
}

node_struct *find_node(node_struct *head, int key, int *count)
{
    while (head != NULL)
    {
        if (head->field > key)
        {
            head = head->left;
            (*count)++;
        }
        else if (head->field < key)
        {
            head = head->right;
            (*count)++;
        }
        else if (head->field == key)
        {
            (*count)++;
            break;
        }
    }
    return head;
}

void print_balanced_tree()
{
    FILE *file;
    int value;
    node_struct *head = NULL;
    file = fopen("val.txt", "r");
    while(fscanf(file, "%d", &value) == 1)
        head = add_node(head, create_node(value), 1);
    walk_tree(head, NULL);
    fclose(file);
    printf("Infix :");
    inorder(head);
    printf("\n------------------------------\n");
    printf("Prefix :");
    preorder(head);
    printf("\n------------------------------\n");
    printf("Postfix :");
    postorder(head);
    printf("\n------------------------------\n");
    free_tree(head);
}

int find_in_tree(int *count_compare_ddp)
{
    FILE *file;
    int value;
    node_struct *head = NULL;
    int val;
    printf("Введите значение для поиска: ");
    scanf("%d", &val);
    file = fopen("val.txt", "r");
    while(fscanf(file, "%d", &value) == 1)
        head = add_node(head, create_node(value), 0);
    node_struct *temp = find_node(head, val, count_compare_ddp);
    if (temp == NULL)
    {
        printf("Количество сравнений : %d\n", *count_compare_ddp);
        free_tree(head);
        return EXIT_FAILURE;
    }
    walk_tree(head, temp);
    fclose(file);
    printf("Количество сравнений : %d\n", *count_compare_ddp);
    free_tree(head);
    return EXIT_SUCCESS;
}

int find_in_balanced_tree(int *count_compare_avl)
{
    FILE *file;
    int value;
    node_struct *head = NULL;
    int val;
    printf("Введите искомое значение: ");
    scanf("%d", &val);
    file = fopen("val.txt", "r");
    while(fscanf(file, "%d", &value) == 1)
        head = add_node(head, create_node(value), 1);
    node_struct *temp = find_node(head, val, count_compare_avl);
    if (temp == NULL)
    {
        printf("Количество сравнений : %d\n", *count_compare_avl);
        free_tree(head);
        return EXIT_FAILURE;
    }
    walk_tree(head, temp);
    fclose(file);
    printf("Количество сравнений : %d\n", *count_compare_avl);
    free_tree(head);
    return EXIT_SUCCESS;
}

int hash_func(int elem, int size)
{
    return elem % size ;
}

void insert_node(node_struct_hash **head, node_struct_hash *node)
{
    if (*head)
    {
        node_struct_hash *temp = *head;
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
    else
        *head = node;
}

int len(node_struct_hash* head)
{
    node_struct_hash* current = head;
    int count = 0;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

node_struct_hash *create_hash_node(int value)
{
    node_struct_hash *node = malloc(sizeof(node_struct_hash));
    node->value = value;
    node->next = NULL;

    return node;
}

int insert_open_hash_table(node_struct_hash ***array, size_t size, int max)
{
    FILE *file;
    int value;
    int position;

    *array = (node_struct_hash**)malloc(size * sizeof(node_struct_hash*));
    for (int i = 0; i < (int)size; i++)
        (*array)[i] = NULL;
    
    file = fopen("val.txt", "r");
    while(fscanf(file, "%d", &value) == 1)
    {
        position = hash_func(value, (int)size);
        insert_node(&((*array)[position]), create_hash_node(value));
    }
    for (int i = 0; i < (int)size; i++)
        if (len((*array)[i]) > max)
            return EXIT_FAILURE;
        
    fclose(file);
    return EXIT_SUCCESS;
}

void free_open_table(node_struct_hash **array, size_t size)
{
    node_struct_hash *temp;
    for(size_t i = 0; i < size; i++)
    {
        while((array)[i] != NULL)
        {
            temp = (array)[i];
            (array)[i] = (array)[i]->next;
            free(temp);
        }
    }
    free(array);
}

void print_open_hash_table(node_struct_hash **array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", i);
        node_struct_hash *temp = array[i];
        if (temp)
        {
            while(temp->next)
            {
                printf (" -> %d", temp->value);
                temp = temp->next;
            }
            printf (" -> %d", temp->value);
            printf(" -> NULL\n");
        }
        else printf(" -> NULL\n");
        printf("\n");
    }
    printf("\n");
}

void create_table(node_struct_hash ***array_op, int *size, int *max)
{
    FILE *file;
    int value;
    int temp;
    file = fopen("val.txt", "r");
    *size = 0;
    while(fscanf(file, "%d", &value) == 1)
        *size = *size + 1;
    fclose(file);
    printf("Введите максимальное сравнение: ");
    scanf("%d", max);

    temp = insert_open_hash_table(array_op, (size_t)*size, *max);
    printf("Таблица: \n");
    print_open_hash_table(*array_op, *size);

    if (temp == EXIT_FAILURE)
    {
        free_open_table(*array_op, (size_t)*size);
        *array_op = NULL;
        *size = 1;
        while (insert_open_hash_table(array_op, (size_t)*size, *max) == EXIT_FAILURE)
            *size = *size * 2;
    }
}
int find_num_in_open_hash_table(node_struct_hash **array, int size, int value, int *count)
{
    int i = hash_func(value, size);
    node_struct_hash *arr = array[i];
    while(arr)
    {
        (*count)++;
        if (arr->value == value)
        {
            return 1;
        }
        arr = arr->next;
    }

    return 0;
}

void clean_buff(FILE *file)
{
    char ch;
    while ((ch = getc(file)) != '\n' && ch != EOF);
}

void print_menu(void)
{
    printf("\n---------Menu---------\n");
    printf("Для дерева:\n");
    printf("1 - Распечатать обычное дерево\n");
    printf("2 - Распечатать сбалансированное дерево\n");
    printf("3 - Поиск в обычном дереве\n");
    printf("4 - Поиск в сбалансированном дереве\n\n");
    printf("Для ХЭШ-Таблиц:\n");
    printf("5 - Создать хэш-таблицу\n");
    printf("6 - Распечатать хэш-таблицу\n");
    printf("7 - Поиск в хэш-таблице\n\n");
    printf("Для всех:\n");
    printf("8 - Эффективность\n");
    printf("0 - Выход\n");
    printf("----------------------\n\n");
    printf("Ваш выбор:");
}

int main(void)
{
    int choice;
    int count_compare_ddp = 0;
    int count_compare_avl = 0;
    int count_compare_hash = 0;
    node_struct_hash **array_op = NULL;
    int size = 0;
    int max = 0;

    while (true)
    {
        print_menu();
        if (scanf("%d", &choice) != 1)
        {
            clean_buff(stdin);
            printf("Некорректный выбор, попробуйте снова!\n");
            continue;
        }
        if (choice == 0)
        {
            printf("Выход...\n\n");
            break;
        }
        else if (choice == 1)
        {
            print_tree();
        }
        else if (choice == 2)
        {
            print_balanced_tree();
        }
        else if (choice == 3)
        {
            find_in_tree(&count_compare_ddp);
            count_compare_ddp = 0;
        }
        else if (choice == 4)
        {
            find_in_balanced_tree(&count_compare_avl);
            count_compare_avl = 0;
        }
        else if(choice == 5)
        {
            create_table(&array_op, &size, &max);
        }
        else if(choice == 6)
        {
            print_open_hash_table(array_op, size);
        }
        else if (choice == 7)
        {
            int val;
            int temp;
            if (array_op == NULL)
                create_table(&array_op, &size, &max);
    
            printf("Введите значение для поиска: ");
            if (scanf("%d", &val) != 1)
            {
                clean_buff(stdin);
                printf("Некорректное значение.\n");
                continue;
            }
            temp = find_num_in_open_hash_table(array_op, size, val, &count_compare_hash);
            if (temp)
            {
                printf("Количество : %d\n", count_compare_hash);
                printf("НАЙДЕНО\n");
            }
            else
            {
                printf("Количество : %d\n", count_compare_hash);
                printf("НЕ НАЙДЕНО\n");
            }
            count_compare_hash = 0;

        }
        else if (choice == 8)
        {
            long int tm = 0, tms = 0;
            long int time_ddp = 0;
            long int time_avl = 0;
            long int time_hash = 0;
            long int time_file = 0;
            long int memory_ddp = 0;
            long int memory_avl = 0;
            long int memory_hash= 0;
            long int memory_file = 0;
            int count_compare_file = 0;
            int value;
            node_struct *head = NULL;
            int val;
            node_struct* node = NULL;

            printf("Введите значение для поиска: ");
            if (scanf("%d", &val) != 1)
            {
                clean_buff(stdin);
                printf("Некорректное значение.\n");
                continue;
            }
            FILE *file;
            int proverka = 0;
            file = fopen("val.txt", "r");
            while(fscanf(file, "%d", &value) == 1)
            {
                if (val == value)
                {
                    proverka++;
                    break;
                }
            }
            fclose(file);

            if (proverka == 0)
            {
                printf("Нет такого номера!\n");
                return EXIT_FAILURE;
            }

            file = fopen("val.txt", "r");
            while (fscanf(file, "%d", &value) == 1)
                head = add_node(head, create_node(value), 0);

            tm = tic();
            node = find_node(head, val, &count_compare_ddp);
            free_tree(node);
            tms = tic();

            fclose(file);

            time_ddp = tms-tm;

            head = NULL;
            file = fopen("val.txt", "r");
            while(fscanf(file, "%d", &value) == 1)
                head = add_node(head, create_node(value), 1);
            tm = tic();
            node = find_node(head, val, &count_compare_avl);
            tms = tic();
            fclose(file);
            free_tree(head);
            time_avl = tms-tm;

            if (array_op != NULL)
            {
                free_open_table(array_op, (size_t)size);
                array_op = NULL;
                size = 0;
            }
            create_table(&array_op, &size, &max);
            time_hash = 0;
            tm = tic();
            find_num_in_open_hash_table(array_op, size, val, &count_compare_hash);
            tms = tic();
            time_hash = tms-tm;
            file = fopen("val.txt", "r");
            time_file = 0;
            tm = tic();
            while(fscanf(file, "%d", &value) == 1)
            {
                count_compare_file++;
                if (value == val)
                {
                    tms = tic();
                    break;
                }
            }

            fclose(file);
            time_file = tms-tm;

            long int count_num_in_file = 0;
            file = fopen("val.txt", "r");
            while(fscanf(file, "%d", &value) == 1)
                count_num_in_file++;
            fclose(file);
            memory_ddp = count_num_in_file * sizeof (node_struct);
            memory_avl = count_num_in_file * sizeof (node_struct);
            memory_hash = count_num_in_file * sizeof(node_struct_hash) + sizeof (array_op);
            memory_file = 0;
            printf("\tDDP\tAVL\tHASH\tFILE\n");
            printf("Время\t%lu\t%lu\t%lu\t%lu\n", time_ddp, time_avl, time_hash, time_file);
            printf("Память\t%lu\t%lu\t%lu\t%lu\n", memory_ddp, memory_avl, memory_hash, memory_file);
            printf("Количество\t%d\t%d\t%d\t%d\n", count_compare_ddp, count_compare_avl, count_compare_hash, count_compare_file);
            count_compare_ddp = 0;
            count_compare_avl = 0;
            count_compare_hash = 0;
            count_compare_file = 0;
        }
        clean_buff(stdin);
    }
    return 0;
}
