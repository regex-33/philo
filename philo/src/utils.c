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

void	log_state_change(int philosopher_id, const char *state,
		long long timestamp, long long first_time)
{
	(void)first_time;
	printf("%lld %d %s\n", timestamp, philosopher_id, state);
}

void	print_status(long timestamp, int id, char *msg)
{
	printf("%ld %d %s\n", timestamp, id, msg);
}

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
