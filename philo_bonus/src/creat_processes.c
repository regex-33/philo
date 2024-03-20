/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:19:38 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 18:12:10 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	create_death_checker(pthread_t *death_checker, t_philo *philo)
{
	if (pthread_create(death_checker, NULL, death_check_routine,
			(void *)philo) != 0)
	{
		perror("pthread_create failed");
		exit(EXIT_FAILURE);
	}
	if (pthread_detach(*death_checker) != 0)
	{
		perror("pthread_detach failed");
		exit(EXIT_FAILURE);
	}
}

void	perform_actions_while_eating(t_philo *philo)
{
	take_forks(philo);

	print_status(philo, get_time() - philo->data->start_time, philo->id, "is eating");

	usleep(philo->data->time_to_eat * 1000);
	sem_wait(philo->race_data);
	philo->last_meal = get_time();
	sem_post(philo->race_data);
	put_forks(philo);
}

void	perform_actions_while_sleeping(t_philo *philo)
{

	print_status(philo, get_time() - philo->data->start_time, philo->id,
		"is sleeping");

	usleep(philo->data->time_to_sleep * 1000);
}

void	philosopher_process(t_philo *philo)
{
	pthread_t	death_checker;

	create_death_checker(&death_checker, philo);
	while (1)
	{
		perform_actions_while_eating(philo);
		perform_actions_while_sleeping(philo);

		print_status(philo, get_time() - philo->data->start_time, philo->id,
			"is thinking");

		if (philo->check_flag)
		{
			philo->num_of_meals++;
			if (philo->num_of_meals == philo->num_of_times_to_eat)
				break ;
		}
	}
}

void	create_processes(t_philo *philos, int num_of_philosophers)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < num_of_philosophers)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			philosopher_process(&philos[i]);
			exit(EXIT_SUCCESS);
		}
		else
			philos[i].pid = pid;
		i++;
	}
}
