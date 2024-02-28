/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 07:52:02 by yachtata          #+#    #+#             */
/*   Updated: 2024/02/25 07:52:51 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// long long	current_time_millis(long long first_time)
// {
// 	struct timeval	current_time;

// 	gettimeofday(&current_time, NULL);
// 	return ((current_time.tv_sec * 1000LL + current_time.tv_usec / 1000)
// 		- first_time);
// }

void	log_state_change(int philosopher_id, const char *state,
		long long timestamp, long long first_time)
{
	(void)first_time;
	printf("%lld %d %s\n", timestamp, philosopher_id, state);
}

void print_status(long timestamp, int id, char *msg)
{
  //  printf("\n time %ld\n", timestamp);
    printf("%ld %d %s\n", timestamp, id, msg);
}

long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	check_time_to_die(int id, long long last_meal, t_philosopher *philo)
{
	// printf("current : %lld | first_time : %lld\n",
	//current_time_millis(first_time),  die);
	if (get_time() - last_meal >= philo->data->die)
	{
		print_status(get_time() - philo->data->start_time, id, "is died");
		//log_state_change(id, "died", die);
		exit(1);
	}
}

void init_mutex(pthread_mutex_t *forks, int num_of_phils)
{
	int	i;

	i = 0;
	while (i < num_of_phils + 1)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void destroy_mutex(pthread_mutex_t *forks, int num_of_phils)
{
	int i;

	i = 0;
	while (i < num_of_phils + 1)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void wait_threads(t_philosopher *philosophers, int num_of_phils)
{
	int	i;

	i = 0;
	while (i < num_of_phils + 1)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}