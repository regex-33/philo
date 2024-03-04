#include "../inc/philosophers.h"

int if_die(t_philosopher *philo)
{
    	pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->philosopher_died)
		{
            pthread_mutex_unlock(&philo->data->death_mutex);
            return 1;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);
        return 0;
}

void *check_time_of_threads(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    int num_philo = philo[0].data->num_of_phils;
    int i = 0;

    while (1)
    {
        if (get_time() - philo[i].last_meal >= philo[i].data->die)
        {
	        pthread_mutex_lock(&philo->data->death_mutex);
            philo->data->philosopher_died = 1;
            pthread_mutex_unlock(&philo->data->death_mutex);
			print_status(get_time() - philo[i].data->start_time, philo[i].id, "is die");
            break ;
        }
        usleep(3000);
        i = (i + 1) % num_philo;
    }
    return NULL;
}

int	initialize_vars(t_time *data, int num_of_times_to_eat)
{
	int				i;
	t_philosopher	philosophers[data->num_of_phils + 1];
	pthread_mutex_t	forks[data->num_of_phils];

	i = 0;
	data->start_time = get_time();
	init_mutex(forks, data->num_of_phils);
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
		pthread_create(&philosophers[i].thread, NULL, philosopher_thread, &philosophers[i]);
		//usleep (500);
		i++;
	}
	pthread_create(&philosophers[i].thread, NULL, check_time_of_threads, &philosophers);
	wait_threads(philosophers, data->num_of_phils);
	destroy_mutex(forks, data->num_of_phils);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_time			data;
	int				num_of_times_to_eat;

	if (argc < 5 || argc > 6)
    {
        printf("./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n");
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
	pthread_mutex_init(&data.death_mutex, NULL);
	data.philosopher_died = 0;
	if (!initialize_vars(&data, num_of_times_to_eat))
		return (1);
	return (0);
}

/*
void *philosopher_thread(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    int philo_id = philo->id;
    pthread_mutex_t *left_fork = philo->left_fork;
    pthread_mutex_t *right_fork = philo->right_fork;


    while (1)
    {
        if (philo_id % 2)
        {
            if (if_die(philo))
                return NULL;
            pthread_mutex_lock(left_fork);
            if (if_die(philo))
                return NULL;
			print_status(get_time() - philo->data->start_time, philo_id, "has taken a fork");
            pthread_mutex_lock(right_fork);
            if (if_die(philo))
                return NULL;
			print_status(get_time() - philo->data->start_time, philo_id, "has taken a fork");
        }
        else
        {
			usleep(500);
            if (if_die(philo))
                return NULL;
            pthread_mutex_lock(right_fork);
            if (if_die(philo))
                return NULL;
			print_status(get_time() - philo->data->start_time, philo_id, "has taken a fork");
            pthread_mutex_lock(left_fork);
            if (if_die(philo))
                return NULL;
			print_status(get_time() - philo->data->start_time, philo_id, "has taken a fork");
        }
        if (if_die(philo))
            return NULL;
		print_status(get_time() - philo->data->start_time, philo_id, "is eating");
		usleep(philo->data->eat * 1000);
		philo->last_meal = get_time();
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);

        if (if_die(philo))
            return NULL;
		print_status(get_time() - philo->data->start_time, philo_id, "is sleeping");
        usleep(philo->data->sleep * 1000);
  
        if (if_die(philo))
            return NULL;
		print_status(get_time() - philo->data->start_time, philo_id, "is thinking");
		if (philo->checker)
		{
			philo->count++;
			if (philo->count >= philo->num_of_times_to_eat)
				break;
		}

		if (if_die(philo))
            return NULL; 
    }
    return NULL;
}
*/