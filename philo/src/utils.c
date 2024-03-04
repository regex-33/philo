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

void	log_state_change(int philosopher_id, const char *state,
		long long timestamp, long long first_time)
{
	(void)first_time;
	printf("%lld %d %s\n", timestamp, philosopher_id, state);
}

void print_status(long timestamp, int id, char *msg)
{
    printf("%ld %d %s\n", timestamp, id, msg);
}

long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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