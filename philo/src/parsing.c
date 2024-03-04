#include "../inc/philosophers.h"

long long	ft_atoi(const char *str)
{
	long long	ps_ng;
	long long	result;

	ps_ng = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		ps_ng *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			result = result * 10 + (*str - 48);
		else
			return (result * ps_ng);
		str++;
	}
	return (result * ps_ng);
}

int is_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0;
        i++;
    }
    return (1);
}

int check_parameters(t_time *data, char **argv)
{
    int     i;

    i = 0;
    while (argv[i])
    {
        if (!is_number(argv[i]))
            return (0);
        if (i == 0)
            data->num_of_phils = ft_atoi(argv[i]);
        else if (i == 1)
            data->die = ft_atoi(argv[i]);
        else if (i == 2)
            data->eat = ft_atoi(argv[i]);
        else
            data->sleep = ft_atoi(argv[i]);
        i++;
    }
    return 1;
}