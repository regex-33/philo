/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:04:11 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 10:04:12 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_mutexes(t_time *data, pthread_mutex_t *forks, int num_of_phils)
{
	int	i;

	i = 0;
	while (i < num_of_phils)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->last_meal_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->died, NULL);
	data->philosopher_died = 0;
	data->flag = 1;
}

void	destroy_mutexes(t_time *data, pthread_mutex_t *forks, int num_of_phils)
{
	int	i;

	i = 0;
	while (i < num_of_phils)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->last_meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->died);
}

void	init_philosophers(t_time *data, pthread_mutex_t *forks,
		t_philosopher *philosophers, int num_of_times_to_eat)
{
	int	i;

	i = 0;
	while (i < data->num_of_phils)
	{
		if (num_of_times_to_eat > 0)
			philosophers[i].checker = 1;
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % data->num_of_phils];
		philosophers[i].data = data;
		philosophers[i].last_meal = get_time();
		philosophers[i].count = 0;
		philosophers[i].num_of_times_to_eat = num_of_times_to_eat;
		pthread_create(&philosophers[i].thread, NULL, philosopher_thread,
			&philosophers[i]);
		i++;
	}
}

int	initialize_vars(t_time *data, int num_of_times_to_eat)
{
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
	pthread_t		checker_thread;

	forks = malloc(sizeof(pthread_mutex_t) * data->num_of_phils);
	if (!forks)
		return (EXIT_FAILURE);
	philosophers = malloc(sizeof(t_philosopher) * data->num_of_phils);
	if (!philosophers)
		return (EXIT_FAILURE);
	data->start_time = get_time();
	init_mutexes(data, forks, data->num_of_phils);
	init_philosophers(data, forks, philosophers, num_of_times_to_eat);
	pthread_create(&checker_thread, NULL, check_time_of_threads, philosophers);
	pthread_detach(checker_thread);
	ft_usleep(500);
	wait_threads(philosophers, data->num_of_phils);
	destroy_mutexes(data, forks, data->num_of_phils);
	free(philosophers);
	free(forks);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_time	data;
	int		num_of_times_to_eat;

	num_of_times_to_eat = 0;
	if (argc < 5 || argc > 6)
		return (ft_putendl_fd("./philo <number_of_philosophers> <time_to_die> "
				"<time_to_eat> <time_to_sleep>", 2), 1);
	argv++;
	if (!check_parameters(&data, argv))
		return (ft_putendl_fd("philo: pase error", 2), 1);
	if (argc == 6)
	{
		if (!is_number(argv[4]))
			return (0);
		num_of_times_to_eat = ft_atoi(argv[4]);
		if (num_of_times_to_eat <= 0)
			return (0);
	}
	if (!initialize_vars(&data, num_of_times_to_eat))
		return (1);
	return (0);
}
