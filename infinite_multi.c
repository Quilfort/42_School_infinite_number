#include <unistd.h>
#include <stdbool.h>

int ft_strlen(char *string)
{
    int i = 0;
    while(string[i])
        i++;
    return (i);
}

bool is_min (char *s1, char *s2)
{
    if (s1[0] == '-' && s2[0] == '-')
        return (false);
    if (s1[0] == '-' || s2[0] == '-')
        return (true);
    return (false);
}

int main (int argc, char *argv[])
{
    if (argc != 3)
        return (1);
    if (argv[1][0] == '0'|| argv[2][0] == '0')
    {
        write(1, "0\n", 2);
        return (0);
    }

    int len_s1 = ft_strlen(argv[1]);
    int len_s2 = ft_strlen(argv[2]);

    int a[1000] = {0};
    int b[1000] = {0};
    int res[2000] = {0};
    int i, j, temp;
    char c;

    bool min = is_min(argv[1], argv[2]);

    for (i = len_s1 - 1, j = 0; i >= 0 && argv[1][i] != '-'; i--, j++)
        a[j] = argv[1][i] - '0';
    for (i = len_s2 - 1, j = 0; i >= 0 && argv[2][i] != '-'; i--, j++)
        b[j] = argv[2][i] - '0';

    for (i = 0; i < len_s2; i++)
    {
        for (j = 0; j < len_s1; j++)
            res[i + j] += a[j] * b[i];
    }

    for (i = 0; i < len_s1 + len_s2; i++)
    {
        temp = res[i] / 10;
        res[i] = res[i] % 10;
        res[i + 1] += temp;
    }

    for (i = len_s1 + len_s2; i >= 0; i--)
    {
        if (res[i] > 0)
            break ;
    }

    if (min)
        write (1, "-", 1);
    
    for (; i >= 0; i--)
    {
        c = res[i] + '0';
        write(1, &c, 1);
    }
    write (1, "\n", 1);
    return (0);
}