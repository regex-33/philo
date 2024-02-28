#include "../inc/philosophers.h"

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
            pthread_mutex_lock(left_fork);
			print_status(get_time() - philo->data->start_time, philo_id, "has taken a fork");
            pthread_mutex_lock(right_fork);
			print_status(get_time() - philo->data->start_time, philo_id, "has taken a fork");
        }
        else
        {
			usleep(500);
            pthread_mutex_lock(right_fork);
			print_status(get_time() - philo->data->start_time, philo_id, "has taken a fork");
            pthread_mutex_lock(left_fork);
			print_status(get_time() - philo->data->start_time, philo_id, "has taken a fork");
        }
		print_status(get_time() - philo->data->start_time, philo_id, "is eating");
		usleep(philo->data->eat * 1000);
		philo->last_meal = get_time();
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		print_status(get_time() - philo->data->start_time, philo_id, "is sleeping");
        usleep(philo->data->sleep * 1000);
    	
		print_status(get_time() - philo->data->start_time, philo_id, "is thinking");

    }
    return NULL;
}

void *check_time_of_threads(void *arg)
{
    t_philosopher *philosophers = (t_philosopher *)arg;
    int num_philosophers = philosophers[0].data->num_of_phils;
    int i = 0;

    while (1)
    {
        check_time_to_die(philosophers[i].id, philosophers[i].last_meal, philosophers);
        usleep(10000);
        i = (i + 1) % num_philosophers;
    }
    return NULL;
}

int	initialize_vars(t_time *data)
{
	int				i;
	t_philosopher	philosophers[data->num_of_phils + 1];
	pthread_mutex_t	forks[data->num_of_phils];

	i = 0;
	data->start_time = get_time();
	init_mutex(forks, data->num_of_phils);

	while (i < data->num_of_phils)
	{
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % data->num_of_phils];
		philosophers[i].data = data;
		philosophers[i].last_meal = get_time();
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
	if (argc != 5)
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
	if (!initialize_vars(&data))
		return (1);
	return (0);
}

