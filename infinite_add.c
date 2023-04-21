#include <stdbool.h>
#include <unistd.h>

int ft_strlen (char *string)
{
    int i = 0;
    while (string[i])
        i++;
    return i;
}

int loop_length(int len_s1, int len_s2)
{
	if (len_s2 > len_s1)
        return (len_s2 + 2);
    return (len_s1 + 2);            
}

bool is_min(char *string)
{
    if (string[0] == '-')
        return (true);
    return false;
}

int compare_string(char *neg, char *pos)
{
	int i = 0;
	int j = 1;
	int len = ft_strlen(pos);

	while (i < len)
	{
		if (neg[j] > pos[i])
			return (1);
		if (neg[j] < pos[i])
			return (2);
		i++;
		j++;	
	}
	return (0);
}

void make_res(int *first, int *second, int *res, int loop_len)
{
	int i;
	for (i = 0; i < loop_len; i++)
    	res[i] = first[i] - second[i];
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        return 0;

    if (argv[1][0] == '0' && argv[2][0] == '0')
    {
        write (1, "0\n", 2);
        return 0;
    }

    int len_s1 = ft_strlen(argv[1]);
    int len_s2 = ft_strlen(argv[2]);
    bool min_s1 = is_min(argv[1]);
    bool min_s2 = is_min(argv[2]);
	bool print_min = false;

    int loop_len = loop_length(len_s1, len_s2);
    int a[1000] = {0};
    int b[1000] = {0};
    int res[2000] = {0};
    int i, j, temp;

    char c;

	int first = len_s1;
	int second = len_s2;
	if (min_s1)
		first += -1;

	if (min_s2)
		second += -1;		

	if (first >= second)
	{
		for (i = len_s1 - 1, j = 0; i >= 0 && argv[1][i] != '-'; i--, j++)
        	a[j] = argv[1][i] - '0';
		for (i = len_s2 - 1, j = 0; i >= 0 && argv[2][i] != '-'; i--, j++)
       		b[j] = argv[2][i] - '0';
	}
	else
	{
		for (i = len_s2 - 1, j = 0; i >= 0 && argv[2][i] != '-'; i--, j++)
        	a[j] = argv[2][i] - '0';
		for (i = len_s1 - 1, j = 0; i >= 0 && argv[1][i] != '-'; i--, j++)
       		b[j] = argv[1][i] - '0';
	}

    if (min_s1 == min_s2)
    {
        for (i = 0; i < loop_len; i++)
            res[i] += a[i] + b[i];
    }
	else
	{
		if (min_s1)
		{
			if (len_s1 == len_s2 + 1)
			{
				if (compare_string(argv[1], argv[2]) == 0)
				{
					write (1, "0\n", 2);
        			return 0;
				}
				if (compare_string(argv[1], argv[2]) == 1)
				{
					print_min = true;
					make_res(a, b, res, loop_len);
				}
				else
					make_res(b, a, res, loop_len);
			}
			else
			{
				if (len_s1 > len_s2 + 1)
					print_min = true;
				make_res(a, b, res, loop_len);
			}
		}
		else if (min_s2)
		{
			if (len_s2 == len_s1 + 1)
			{
				if (compare_string(argv[2], argv[1]) == 0)
				{
					write (1, "0\n", 2);
        			return 0;
				}
				if (compare_string(argv[2], argv[1]) == 1)
				{
					print_min = true;
					make_res(a, b, res, loop_len);
				}
				else
					make_res(b, a, res, loop_len);
			}
			else
			{
				if (len_s2 > len_s1 + 1)
					print_min = true;
				make_res(a, b, res, loop_len);
			}
		}
	}

	if (min_s1 == min_s2)
	{
		for (i = 0; i < loop_len + 1; i++)
		{
			temp = res[i] / 10;
			res[i] = res[i] % 10;
			res[i + 1] += temp;
		}
	}
	else
	{
		for (i = 0; i < loop_len; i++)
		{
			if (res[i] < 0)
			{
				res[i] += 10;
				temp = 1;
			}
			else
				temp = 0;
			res[i + 1] -= temp;
		}
	}

    for (i = loop_len + 1; i >= 0; i--)
    {
        if (res[i] > 0)
            break;
    }

	if (min_s1 == true && min_s2 == true)
		write(1, "-", 1);
	else if (print_min == true)
		write(1, "-", 1);

    for (; i >= 0; i--)
    {
        c = res[i] + '0';
        write(1, &c, 1);
    }

    write(1, "\n", 1);
    return (0);
}
