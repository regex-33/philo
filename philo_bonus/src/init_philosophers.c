/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:19:48 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/03 09:19:49 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	*death_check_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (1)
	{
		if (get_time() - philo->last_meal >= philo->data->time_to_die)
		{
			sem_wait(philo->lock);
			print_status(get_time() - philo->data->start_time, philo->id,
				"died");
			sem_post(philo->lock);
			exit(EXIT_FAILURE);
		}
		ft_usleep(10000);
	}
	return (NULL);
}

void	initialize_forks(sem_t **forks, int num_of_philosophers)
{
	*forks = sem_open("/forks", O_CREAT | O_EXCL, 0666, num_of_philosophers);
	if (*forks == SEM_FAILED)
	{
		printf("sem_open failed\n");
		exit(EXIT_FAILURE);
	}
	sem_unlink("/forks");
}

void	initialize_philosopher(t_philo *philo, int id, t_time *data,
		sem_t *forks)
{
	struct timeval	current_time;

	philo->check_flag = 0;
	philo->id = id + 1;
	philo->num_of_meals = 0;
	philo->forks = forks;
	philo->pid = 0;
	philo->num_of_times_to_eat = data->num_of_times_to_eat;
	philo->data = data;
	gettimeofday(&current_time, NULL);
	philo->last_meal = current_time.tv_sec * 1000LL + current_time.tv_usec
		/ 1000;
	philo->lock = sem_open("/lock", O_CREAT | O_EXCL, 0666, 1);
	if (philo->lock == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
	if (data->num_of_times_to_eat > 0)
		philo->check_flag = 1;
	sem_unlink("/lock");
}

void	init_philosophers(t_time *data, t_philo *philos,
		int num_of_philosophers)
{
	sem_t	*forks;
	int		i;

	i = 0;
	initialize_forks(&forks, data->num_of_philosophers);
	while (i < num_of_philosophers)
	{
		initialize_philosopher(&philos[i], i, data, forks);
		i++;
	}
}
