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
	usleep(500);
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

	if (argc < 5 || argc > 6)
	{
		printf("./philo <number_of_philosophers> <time_to_die> "
			"<time_to_eat> <time_to_sleep>\n");
		return (1);
	}
	argv++;
	if (!check_parameters(&data, argv))
	{
		printf("error\n");
		return (1);
	}
	if (argc == 6)
	{
		if (!is_number(argv[4]))
			return (0);
		num_of_times_to_eat = ft_atoi(argv[4]);
	}
	if (!initialize_vars(&data, num_of_times_to_eat))
		return (1);
	return (0);
}

/*

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
		if (philo_id % 2)
			odd_philosopher_action(philo, left_fork, right_fork);
		else
			even_philosopher_action(philo, left_fork, right_fork);
		if (if_die(philo))
			return (NULL);
		philo_action_after_eating(philo, philo_id);
		if (if_die(philo))
			return (NULL);
		philo_action_after_sleeping(philo, philo_id);
		if (if_die(philo))
			return (NULL);
		if (!philo_action_after_thinking(philo, philo_id))
			return (NULL);
	}
	return (NULL);
}

void	*check_time_of_threads(void *arg)
{
	int				i;
	t_philosopher	*philosophers;
	int				num_philo;

	philosophers = (t_philosopher *)arg;
	num_philo = philosophers[0].data->num_of_phils;
	while (1)
	{
		i = 0;
		while (i < num_philo)
		{
			pthread_mutex_lock(&philosophers[i].data->died);
			if (get_time()
				- philosophers[i].last_meal >= philosophers[i].data->die)
			{
				pthread_mutex_lock(&philosophers->data->death_mutex);
				philosophers->data->philosopher_died = 1;
				pthread_mutex_unlock(&philosophers->data->death_mutex);
				print_status(get_time() - philosophers[i].data->start_time,
					philosophers[i].id, "is die");
				pthread_mutex_unlock(&philosophers[i].data->died);
				return (NULL);
			}
			pthread_mutex_unlock(&philosophers[i].data->died);
			usleep(3000);
			i++;
		}
	}
	return (NULL);
}

int	initialize_vars(t_time *data, int num_of_times_to_eat)
{
	int				i;
	t_philosopher	philosophers[data->num_of_phils];
	pthread_mutex_t	forks[data->num_of_phils];
	pthread_t		checker_thread;

	data->start_time = get_time();
	init_mutex(forks, data->num_of_phils);
	pthread_mutex_init(&data->last_meal_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->died, NULL);
	data->philosopher_died = 0;
	data->flag = 1;
	for (i = 0; i < data->num_of_phils; i++)
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
	}
	pthread_create(&checker_thread, NULL, check_time_of_threads, philosophers);
	pthread_detach(checker_thread);
	usleep(500);
	wait_threads(philosophers, data->num_of_phils);
	destroy_mutex(forks, data->num_of_phils);
	return (EXIT_SUCCESS);
}

*/
