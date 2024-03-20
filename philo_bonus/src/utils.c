/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:19:34 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 18:13:48 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

sem_t print_lock;

void	take_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	print_status(philo, get_time() - philo->data->start_time, philo->id,
		"has taken a fork");
	sem_wait(philo->forks);
	print_status(philo, get_time() - philo->data->start_time, philo->id,
		"has taken a fork");
}

void	put_forks(t_philo *philo)
{
	sem_post(philo->forks);
	print_status(philo, get_time() - philo->data->start_time, philo->id,
		"has put a fork");
	usleep(70);
	sem_post(philo->forks);
	print_status(philo, get_time() - philo->data->start_time, philo->id,
		"has put a fork");
	usleep(70);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_status(t_philo *philo,long timestamp, int id, char *msg)
{
	(void *)philo;
    sem_wait(philo->print_lock);

    printf("%ld %d %s\n", timestamp, id, msg);

    sem_post(philo->print_lock);
}