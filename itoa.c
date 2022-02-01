/*
** EPITECH PROJECT, 2021
** itoa
** File description:
** int to char*
*/

int my_swap(char *a, char *b)
{
    char p = *a;
    *a = *b;
    *b = p;
    return (0);
}

char *my_revstr(char *str)
{
    int j = 0;
    int i = 0;

    while (str[i] != '\0')
        i++;
    while (i > j) {
        i--;
        my_swap(str + i, str + j);
        j++;
    }
    return (str);
}

char* itoa(int num, char* str, int base)
{
    int i = 0;
    int neg = 0;
 
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if (num < 0 && base == 10) {
        neg = 1;
        num = -num;
    }
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
    if (neg == 1)
        str[i++] = '-';
    str[i] = '\0';
    str = my_revstr(str);
    return (str);
}