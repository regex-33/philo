/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:11:09 by yachtata          #+#    #+#             */
/*   Updated: 2024/02/28 12:12:06 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_parameters(t_time *data, char **argv)
{
	int	i;

	i = 0;
	data->num_of_times_to_eat = 0;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			return (0);
		if (i == 0)
			data->num_of_philosophers = ft_atoi(argv[i]);
		else if (i == 1)
			data->time_to_die = ft_atoi(argv[i]);
		else if (i == 2)
			data->time_to_eat = ft_atoi(argv[i]);
		else if (i == 3)
			data->time_to_sleep = ft_atoi(argv[i]);
		else
			data->num_of_times_to_eat = ft_atoi(argv[i]);
		i++;
	}
	data->start_time = get_time();
	return (1);
}

void	cleanup(t_philo *philos, int num_of_philosophers)
{
	int	i;

	i = 0;
	while (i < num_of_philosophers)
	{
		sem_close(philos[i].lock);
		i++;
	}
	sem_close(philos[0].forks);
}
