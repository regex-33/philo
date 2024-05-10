/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:03:54 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 10:03:54 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	odd_philosopher_action(t_philosopher *philo, pthread_mutex_t *left_fork,
		pthread_mutex_t *right_fork)
{
	if (if_die(philo))
		return ;
	pthread_mutex_lock(left_fork);
	if (if_die(philo))
		return ;
	print_status(get_time() - philo->data->start_time, philo->id,
		"has taken a fork");
	pthread_mutex_lock(right_fork);
	if (if_die(philo))
		return ;
	print_status(get_time() - philo->data->start_time, philo->id,
		"has taken a fork");
	return ;
}

void	even_philosopher_action(t_philosopher *philo,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	ft_usleep(500);
	if (if_die(philo))
		return ;
	pthread_mutex_lock(right_fork);
	if (if_die(philo))
		return ;
	print_status(get_time() - philo->data->start_time, philo->id,
		"has taken a fork");
	pthread_mutex_lock(left_fork);
	if (if_die(philo))
		return ;
	print_status(get_time() - philo->data->start_time, philo->id,
		"has taken a fork");
	return ;
}

void	philo_action_after_eating(t_philosopher *philo, int philo_id)
{
	long	time;

	print_status(get_time() - philo->data->start_time, philo_id, "is eating");
	time = get_reamining_time(philo, philo->data->eat);
	if (time < philo->data->eat)
	{
		ft_usleep(time);
		philo->data->philosopher_died = 1;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	else
		ft_usleep(philo->data->eat * 1000);
	put_time_stamp_memset(&philo->last_meal);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_action_after_sleeping(t_philosopher *philo, int philo_id)
{
	long	time;

	print_status(get_time() - philo->data->start_time, philo_id, "is sleeping");
	time = get_reamining_time(philo, philo->data->sleep);
	if (time < philo->data->sleep)
		ft_usleep(time);
	else
		ft_usleep(philo->data->sleep * 1000);
}

int	philo_action_after_thinking(t_philosopher *philo, int philo_id)
{
	print_status(get_time() - philo->data->start_time, philo_id, "is thinking");
	if (philo->checker)
	{
		philo->count++;
		if (philo->count >= philo->num_of_times_to_eat)
			return (0);
	}
	return (1);
}
