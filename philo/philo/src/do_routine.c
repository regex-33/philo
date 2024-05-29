/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:03:33 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 10:03:34 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	if_die(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->philosopher_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

int	check_for_philosopher_death(t_philosopher *philosophers, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (if_die(&philosophers[i]))
			return (0);
		pthread_mutex_lock(&philosophers[i].data->died);
		if (get_time() - philosophers[i].last_meal >= philosophers[i].data->die)
		{
			memset(&philosophers->data->philosopher_died, 0, sizeof(long));
			memset(&philosophers->data->philosopher_died, 1, 1);
			print_status(get_time() - philosophers[i].data->start_time,
				philosophers[i].id, "is die");
			pthread_mutex_unlock(&philosophers[i].data->died);
			return (0);
		}
		pthread_mutex_unlock(&philosophers[i].data->died);
		ft_usleep(3000);
		i++;
	}
	return (1);
}

void	*check_time_of_threads(void *arg)
{
	t_philosopher	*philosophers;
	int				num_philo;

	philosophers = (t_philosopher *)arg;
	num_philo = philosophers[0].data->num_of_phils;
	while (1)
	{
		if (!check_for_philosopher_death(philosophers, num_philo))
			return (NULL);
	}
	return (NULL);
}

int	execute_philosopher_actions(t_philosopher *philo, int philo_id,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	if (philo_id % 2)
		odd_philosopher_action(philo, left_fork, right_fork);
	else
		even_philosopher_action(philo, left_fork, right_fork);
	if (if_die(philo))
		return (0);
	philo_action_after_eating(philo, philo_id);
	if (if_die(philo))
		return (0);
	philo_action_after_sleeping(philo, philo_id);
	if (if_die(philo))
		return (0);
	if (!philo_action_after_thinking(philo, philo_id))
		return (0);
	return (1);
}

void	*philosopher_thread(void *arg)
{
	t_philosopher	*philo;
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	philo = (t_philosopher *)arg;
	philo_id = philo->id;
	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	while (1)
	{
		if (if_die(philo))
			return (NULL);
		if (!execute_philosopher_actions(philo, philo_id, left_fork,
				right_fork))
			return (NULL);
	}
	return (NULL);
}
