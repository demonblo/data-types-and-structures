#include <stdio.h>
#include <math.h>

#define OK             0
#define EMPTY         -1
#define ZERO_DIV      -2
#define LENGTH_ERRORR -3
#define INPUT_ERROR   -4
#define TOO_BIG_POWER -5
#define PLS           -6
typedef struct
{
    char mant_sign;
    int mant[70];
    int mant_len;
    int power;

} num;

int input_int(num* number)
{
    char c;
    int cnt = 0;
    char stream[100];

    number -> mant_sign = 0;
    number -> mant_len = 0;
    number -> power = 0;

    while (((c = getc(stdin)) != '\n') && (c != '\0'))
        stream[cnt++] = c;
    stream[cnt] = '\0';
    char* i = stream;
    int counter_kek = 0;
    for(int lol = 0; lol < cnt; i++)
    {
        if((*i) == '0')
            counter_kek++;
        lol++;
    }



    if (cnt == 0)
        return EMPTY;

    i = stream;
    if (*i == '+' || *i == '-')
    {
        if (*i == '-')
            (*number).mant_sign = 1;
        char* j = i;
        while (*j != '\0')
        {
            *j = *(j + 1);
            j++;
        }
    }
    for (; *i != '\0'; i++)
    {
        if (('0' <= (*i)) && ((*i) <= '9'));
        else
            return INPUT_ERROR;
    }
    if (counter_kek == cnt)
        return PLS;

    int j = 0;
    int len = 0;
    for (; stream[j] != '\0'; ++j)
        if (('0' <= stream[j]) && (stream[j] <= '9'))
            ++len;
    if (len > 30)
        return LENGTH_ERRORR;

    int dot_pos = 0;
    for (; dot_pos < j && stream[dot_pos] != '.'; dot_pos++)
        ;


    int first_pos;
    if (dot_pos == j)
        first_pos = 0;
    else
        first_pos = dot_pos + 1;

    int last_pos = j;
    int pow_plus = 0;
    for (int k = j - 1; k >= 0; k--)
    {
        int before = 0;
        if (stream[k] != '0' && stream[k] != '.')
            first_pos = k;
        else
            for (int q = k - 1; q >= 0; q--)
                if (stream[q] != '0')
                {
                    before++;
                    break;
                }
        if (before)
        {
            first_pos = k;
        }
    }

    for (int k = dot_pos - 1; k >= 0; k--)
    {
        int before = 0;
        if (stream[k] != '0')
        {
            pow_plus++;
        }
        else
            for (int q = k - 1; q >= 0; q--)
                if (stream[q] != '0')
                {
                    before++;
                    break;
                }
        if (before)
        {
            pow_plus++;
        }
    }

    for (int k = 0; k < j; k++)
    {
        if (stream[k] != '0')
        {
            last_pos = k;
        }
    }

    int current = 0;
    for (int pos = first_pos; pos <= last_pos; pos++)
        if ('0' <= stream[pos] && stream[pos] <= '9')
        {
            number -> mant[current] = stream[pos] - '0';
            current++;
        }

    current--;
    for (; !(number -> mant[current]); current--)
        ;
    number -> mant_len = current + 1;
    number -> power += pow_plus;

    if (number -> mant_len == 0 && stream[0] != '0')
        return INPUT_ERROR;

    return OK;
}

int input_float(num* number)
{
    char c;
    char dot_cnt = 0;
    char e_cnt = 0;
    int cnt = 0;
    char stream[100];

    number -> mant_sign = 0;
    number -> mant_len = 0;
    number -> power = 0;

    while (((c = getc(stdin)) != '\n') && (c != '\0'))
        stream[cnt++] = c;
    stream[cnt] = '\0';

    if (cnt == 0)
        return EMPTY;

    char* i = stream;
    int kekus = 1;
    for(int lol = 0; lol < cnt; i++)
    {
        if((*i) == '0' || (*i) == '.');
        else if((*i) > '0' && (*i) <= '9')
        {
            kekus = 0;
            break;
        }
        if((*i) == 'E')
        {
            break;
        }
        lol++;
    }


    i = stream;
    if (*i == '+' || *i == '-')
    {
        if (*i == '-')
            (*number).mant_sign = 1;
        char* j = i;
        while (*j != '\0')
        {
            *j = *(j + 1);
            j++;
        }
    }
    for (; *i != '\0' && *i != 'e' && *i != 'E'; i++)
    {
        if (('0' <= (*i)) && ((*i) <= '9'));
        else if (*i == '.')
        {
            if (dot_cnt != 1)
                dot_cnt++;
            else
                return INPUT_ERROR;
        }
        else if (*i == 'E' || *i == 'e')
        {
            if (e_cnt != 1)
                e_cnt++;
            else
                return INPUT_ERROR;
        }
        else
            return INPUT_ERROR;

    }
    if (kekus)
        return ZERO_DIV;

    char power_sign;
    char is_sign = 0;
    if (*i == 'e' || *i == 'E')
    {
        *i = '\0';
        ++i;

        if (*i == '+' || *i == '-')
        {
            is_sign++;
            if (*i == '-')
            {
                power_sign = 1;
            }
            char* j = i;
            while (*j != '\0')
            {
                *j = *(j + 1);
                j++;
            }
        }

        char* set_pos = i;
        while (*i != '\0' && *i != '\n')
        {
            if (('0' <= (*i)) && ((*i) <= '9'))
            {
                number -> power *= 10;
                number -> power += (*i - '0');
            }

            else
                return INPUT_ERROR;
        ++i;
        }

        if (i == set_pos && is_sign)
            return INPUT_ERROR;
        if (power_sign)
            number -> power *= -1;
        if(abs(number -> power) > 99999)
            return TOO_BIG_POWER;
    }

    int j = 0;
    int len = 0;
    for (; stream[j] != '\0'; ++j)
        if (('0' <= stream[j]) && (stream[j] <= '9'))
            ++len;
    if (len > 30)
        return LENGTH_ERRORR;

    int dot_pos = 0;
    for (; dot_pos < j && stream[dot_pos] != '.'; dot_pos++);
    int first_pos;
    if (dot_pos == j)
        first_pos = 0;
    else
        first_pos = dot_pos + 1;
    int last_pos = j;
    int pow_plus = 0;
    for (int k = j - 1; k >= 0; k--)
    {
        int before = 0;
        if (stream[k] != '0' && stream[k] != '.')
            first_pos = k;
        else
            for (int q = k - 1; q >= 0; q--)
                if (stream[q] != '0' && (stream[q] != '.'))
                {
                    before++;
                    break;
                }
        if (before)
            first_pos = k;
    }

    for (int k = dot_pos - 1; k >= 0; k--)
    {
        int before = 0;
        if (stream[k] != '0')
            pow_plus++;
        else
            for (int q = k - 1; q >= 0; q--)
                if (stream[q] != '0')
                {
                    before++;
                    break;
                }
        if (before)
            pow_plus++;
    }

    for (int k = 0; k < j; k++)
    {
        if (stream[k] != '0')
        {
            last_pos = k;
        }
    }

    for (int k = dot_pos + 1; k < j && stream[k] == '0'; k++)
        pow_plus--;

    int current = 0;
    for (int pos = first_pos; pos <= last_pos; pos++)
        if ('0' <= stream[pos] && stream[pos] <= '9')
        {
            number -> mant[current] = stream[pos] - '0';
            current++;
        }

    current--;
    for (; !(number -> mant[current]); current--);
    number -> mant_len = current + 1;
    number -> power += pow_plus;

    if ((number -> mant_len == 0 && stream[0] != '0' && stream[0] != '.'))
        return INPUT_ERROR;

    if ((number -> mant_len == 0 && stream[0] == '.' && stream[1] != '0'))
        return INPUT_ERROR;

    return OK;
}

int before(num* num_cpy, int i)
{
    for (int j = i; j >= 0; j--)
        if (num_cpy -> mant[j] > 0)
            return 1;

    return OK;
}

int is_bigger(num* num_cpy, num* number2, int div_start, int div_end)
{
    for(int i = div_end - 1, j = number2 -> mant_len - 1;
            j >= 0; i--, j--)
    {
        num_cpy -> mant[i] -= number2 -> mant[j];
        if (num_cpy -> mant[i] < 0)
        {
            if (i > 0 && before(num_cpy, i))
                num_cpy -> mant[i - 1] -= 1;
            else
                return OK;
        }
    }

    return 1;
}

int div(num* number1, num* number2, num* div_res)
{
    num num_cpy;
    int div = 0;
    int div_cnt = 0;
    int div_start = 0;
    int div_end = 0;
    int dot = 0;

    if (!(number2 -> mant_len))
        return ZERO_DIV;
    if (!(number1 -> mant_len))
    {
        div_res -> mant_len = 1;
        div_res -> power = 0;
        return 0;
    }
    div_res -> power = (number1 -> power - number2 -> power);
    div_res -> mant_sign = (number1 -> mant_sign + number2 -> mant_sign) % 2;
    if (!(number2 -> mant_len))
        return ZERO_DIV;
    if (!(number2 -> mant_len))
        return 0;
    if (number2 -> mant_len < number1 -> mant_len)
        number2 -> mant_len = number1 -> mant_len;
    else
        number1 -> mant_len = number2 -> mant_len;
    int dot_pos = -1;
    int loop = 0;
    while (1)
    {
        if (!div_start)
            div_end = div_start + (number2 -> mant_len);
        num_cpy = *number1;
        int is_taken = 0;
        while (!is_bigger(&num_cpy, number2, div_start, div_end))
        {
            if (div_end + 1 > number1 -> mant_len)
            {
                if (!dot)
                {
                    dot_pos = loop;
                    dot++;
                    is_taken++;
                }
                else
                {
                    if (!is_taken)
                        is_taken++;
                    else
                    {
                        div_res -> mant[div_cnt] = 0;
                        div_res -> mant_len = ++div_cnt;
                    }
                    if (number1 -> mant[div_start] == 0)
                        div_start++;
                }
            }
            else
            {
                if (!is_taken)
                {
                    is_taken++;

                }
                else
                {
                    div_res -> mant[div_cnt] = 0;
                    div_res -> mant_len = ++div_cnt;
                    div_start++;
                }
            }
            div_end++;
            num_cpy = *number1;
        }

        num_cpy = *number1;
        if (div_end >= 65)
            break;

        num_cpy = *number1;

        div = 0;
        while(1)
        {
            for(int i = div_end - 1,
                j = (number2 -> mant_len) - 1;
                j >= 0 && i >= div_start; i--, j--)
            {
                num_cpy.mant[i] -= number2 -> mant[j];
                if (num_cpy.mant[i] < 0)
                {
                    if (i > 0 && before(&num_cpy, i))
                    {
                        num_cpy.mant[i] += 10;
                        num_cpy.mant[i - 1] -= 1;
                    }
                    else
                        goto end_div;
                }
                if ((num_cpy.mant[i] == 0) && (!before(&num_cpy, i)))
                {
                    div++;
                    goto end_div;
                }

            }
            div++;
        }

        end_div:
        for (int tmp = 0; tmp < div; tmp++)
            for(int i = div_end - 1, j = number2 -> mant_len - 1;
                j >= 0;
                i--, j--)
            {
                number1 -> mant[i] -= number2 -> mant[j];
                if (number1 -> mant[i] < 0)
                {
                    number1 -> mant[i] += 10;
                    number1 -> mant[i - 1] -= 1;
                }
            }

        div_res -> mant[div_cnt] = div;
        div_res -> mant_len = ++div_cnt;
        int i = div_start;
        for(; i < div_end - 1; i++)
            if (number1 -> mant[i])
                break;

        div_start = i;
        loop++;
        int flg = 0;
        for (int i = 0; i <= 31; i++)
            if (number1 -> mant[i])
            {
                flg = 1;
                break;
            }

        if (!flg)
            break;

    }

    if (div_res -> mant_len > 30)
        div_res -> mant_len = 30;
    if (div_res -> mant[30] >= 5)
    {
        (div_res -> mant[29])++;
        for(int i = 29; i >= 1; i--)
        {
            if (div_res -> mant[i] >= 10)
            {
                (div_res -> mant[i]) -= 10;
                (div_res -> mant[i - 1])++;
                if (div_res -> mant[i] == 0)
                    (div_res -> mant_len)--;
            }
        }
        if (div_res -> mant[0] >= 10)
        {
            div_res -> mant[0] -= 10;
            (div_res -> power)++;
            if (div_res -> mant[0] == 0)
                div_res -> mant[0] = 1;
        }
    }

    if (div_res -> mant[29])
        div_res -> mant_len = 30;

    if (dot_pos == -1)
        dot_pos = loop;

    (div_res -> power) += dot_pos;

    if (abs(div_res -> power) > 99999)
        return TOO_BIG_POWER;

    if ((div_res -> mant[29]) == 0 && (div_res -> mant_len == 30))
    {
        int pos = 29;
        while (div_res -> mant[pos] == 0)
        {
            (div_res -> mant_len)--;
            pos--;
        }

    }

    return OK;
}

int main(void)
{
    num number1;
    num number2;
    num div_res;
    int flag = 0;

    printf("Данная программа делит целое число на действительное\n");
    printf("Вводите делимое число и делитель без пробелов!\n\n");
    printf("Формат: [+-]123.456E[+-]123\n");
    printf("Введите делимое число:\n");
    printf("123456789012345678901234567890|\n");
    switch(input_int(&number1))
    {
        case EMPTY:
        printf("Пустой ввод!\n");
        return -1;

        case LENGTH_ERRORR:
        printf("Длина мантисы слишком велика!\n");
        return -1;

        case TOO_BIG_POWER:
        printf("Слишком большая степень числа!\n");
        return -1;

        case INPUT_ERROR:
        printf("Некорректный ввод!\n");
        return -1;

        case PLS:
        flag = 1;
    }

    printf("\nВведите делитель: \n");
    printf("123456789012345678901234567890|\n");

    switch(input_float(&number2))
    {
        case EMPTY:
        printf("Пустой ввод!");
        return -1;

        case LENGTH_ERRORR:
        printf("Слишком длинная мантисса!\n");
        return -1;

        case TOO_BIG_POWER:
        printf("Слишком большая степень числа!\n");
        return -1;

        case INPUT_ERROR:
        printf("Некоректный ввод!\n");
        return -1;

        case ZERO_DIV:
        printf("Нельзя делить на ноль!\n");
        return -1;
    }

    for (int i = number1.mant_len; i < 70; i++)
        number1.mant[i] = 0;
    for (int i = number2.mant_len; i < 70; i++)
        number2.mant[i] = 0;
    for (int i = 0; i < 32; i++)
        div_res.mant[i] = 0;
    switch (div(&number1, &number2, &div_res))
    {
    case OK:
        break;
    case ZERO_DIV:
        printf("Делить на ноль нельзя!\n");
        return -1;
    case TOO_BIG_POWER:
        printf("Слишком большая степень числа!\n");
        return -1;
    }
    if (flag)
    {
        printf("0.0E0\n");
        return -1;
    }
    printf("\nРезультат деления:\n");
    if (div_res.mant_sign)
        printf("-");
    printf("0.");
    for(int i = 0; i < div_res.mant_len; i++)
        printf("%i", div_res.mant[i]);
    printf("E%i\n", div_res.power);

    return OK;
}
