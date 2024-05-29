/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:03:48 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 19:16:11 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

int	check_parameters(t_time *data, char **argv)
{
	int	i;

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
	return (1);
}
