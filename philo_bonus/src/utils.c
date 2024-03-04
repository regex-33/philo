/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:19:34 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/03 09:19:35 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	print_status(get_time() - philo->data->start_time, philo->id,
		"has taken a fork");
	sem_wait(philo->forks);
	print_status(get_time() - philo->data->start_time, philo->id,
		"has taken a fork");
}

void	put_forks(t_philo *philo)
{
	sem_post(philo->forks);
	print_status(get_time() - philo->data->start_time, philo->id,
		"has put a fork");
	sem_post(philo->forks);
	print_status(get_time() - philo->data->start_time, philo->id,
		"has put a fork");
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

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(long timestamp, int id, char *msg)
{
	printf("%ld %d %s\n", timestamp, id, msg);
}
