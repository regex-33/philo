/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:04:24 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 10:04:25 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_threads(t_philosopher *philosophers, int num_of_phils)
{
	int	i;

	i = 0;
	while (i < num_of_phils)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

long	get_reamining_time(t_philosopher *philo, long time_action)
{
	long	remaning_time;

	remaning_time = 0;
	remaning_time = get_time() - philo->last_meal;
	if (time_action > (philo->data->die - remaning_time))
		return (((philo->data->die - remaning_time) * 1000));
	return (time_action * 1000);
}

void	put_time_stamp_memset(long *last_meal)
{
	long	current_time;
	int		i;

	i = 0;
	current_time = get_time();
	memset(last_meal, 0, sizeof(long));
	while (i < 8)
	{
		memset(((unsigned char *)last_meal) + i,
			((unsigned char *)&current_time)[i], 1);
		i++;
	}
}

void	ft_usleep(useconds_t time)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&current, NULL);
		if ((current.tv_sec * 1000000 + current.tv_usec) - (start.tv_sec
				* 1000000 + start.tv_usec) >= time)
			break ;
	}
}
