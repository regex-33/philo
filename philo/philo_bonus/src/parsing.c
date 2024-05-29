/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:11:09 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 19:07:44 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

static const char	*skipwhitespace(const char *c, int *sign)
{
	while (*c == ' ' || *c == '\t' || *c == '\n' || *c == '\r' || *c == '\v'
		|| *c == '\f')
		c++;
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			*sign = -1;
		c++;
	}
	return (c);
}

long long	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	n;
	int					sign;

	i = 0;
	n = 0;
	sign = 1;
	if (str == NULL || (str != NULL && *str == '\0'))
		return (0);
	str = skipwhitespace(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i++] - '0');
		if (n > LLONG_MAX && sign == 1)
			return (-1);
		if (n > LLONG_MAX && sign == -1)
			return (0);
	}
	return (n * sign);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '+'))
			return (0);
		i++;
	}
	return (1);
}

int	check_parameters(t_time *data, char **argv, int i)
{
	i = 0;
	data->num_of_times_to_eat = 0;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			return (-1);
		if (i == 0)
			data->num_of_philosophers = ft_atoi(argv[i]);
		else if (i == 1)
			data->time_to_die = ft_atoi(argv[i]);
		else if (i == 2)
			data->time_to_eat = ft_atoi(argv[i]);
		else if (i == 3)
			data->time_to_sleep = ft_atoi(argv[i]);
		else
		{
			data->num_of_times_to_eat = ft_atoi(argv[i]);
			if (data->num_of_times_to_eat <= 0)
				return (0);
		}
		i++;
	}
	data->start_time = get_time();
	return (1);
}
