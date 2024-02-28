#include "../inc/philo_bonus.h"

long long	current_time_millis(long long first_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000LL + current_time.tv_usec / 1000)
		- first_time);
}

void *death_check_routine(void *philosopher)
{
    t_philo *philo = (t_philo *)philosopher;

    (void ) philo;
    while (1)
    {
        //long timestemp = current_time_millis(philo->last_meal);
        //get_time() - (philo->last_meal.tv_sec * 1000 + (philo->last_meal.tv_usec / 1000));
        //printf("time : %ld || die : %ld\n", timestemp, philo->data->time_to_die);
        if (get_time() - philo->last_meal >= philo->data->time_to_die)
        {
            sem_wait(philo->lock);
            print_status(get_time() - philo->data->start_time, philo->id, "died");
            sem_post(philo->lock);
            exit(EXIT_FAILURE);
        }
        usleep(10000);
    }
    return (NULL);
}


void philosopher_process(t_philo *philo)
{
    pthread_t death_checker;

    if (pthread_create(&death_checker, NULL, death_check_routine, (void *)philo) != 0)
    {
        perror("pthread_create failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_detach(death_checker) != 0)
    {
        perror("pthread_detach failed");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        take_forks(philo);

        sem_wait(philo->lock);
        //printf("get time -> %ld | start->time -> %ld\n", get_time(), philo->data->start_time);
        print_status(get_time() - philo->data->start_time, philo->id, "is eating");
        sem_post(philo->lock);

        usleep(philo->data->time_to_eat * 1000);
        //philo->last_meal = current_time_millis(0);
        philo->last_meal = get_time();
        put_forks(philo);

        sem_wait(philo->lock);
        print_status(get_time() - philo->data->start_time, philo->id, "is sleeping");
        sem_post(philo->lock);

        usleep(philo->data->time_to_sleep * 1000);

        print_status(get_time() - philo->data->start_time, philo->id, "is thinking");

        if (philo->check_flag)
        {
            philo->num_of_meals++;
            //printf("num_of_meals : %d\n", philo->num_of_meals);
            if (philo->num_of_meals == philo->num_of_times_to_eat)
                break;
        }
    }
}

void create_processes(t_philo *philos, int num_of_philosophers)
{
    int i;
    pid_t pid;

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

void    init_philosophers(t_time *data, t_philo *philos, int num_of_philosophers, int num_of_times_to_eat)
{
    sem_t   *forks;
    int     i;
    struct timeval	current_time;

    i = 0;
    forks = sem_open("/forks", O_CREAT | O_EXCL, 0666, num_of_philosophers);
    if (forks == SEM_FAILED)
    {
        printf("sem_open failed\n");
        exit(EXIT_FAILURE);
    }

    sem_unlink("/forks");

    while (i < num_of_philosophers)
    {
        if (num_of_times_to_eat > 0)
            philos[i].check_flag = 1;
        philos[i].id = i + 1;
        philos[i].num_of_meals = 0;
        philos[i].forks = forks;
        philos[i].pid = 0;
        philos[i].num_of_times_to_eat = num_of_times_to_eat;
        philos[i].data = data;
        gettimeofday(&current_time, NULL);
		philos[i].last_meal = current_time.tv_sec * 1000LL + current_time.tv_usec / 1000;
        philos[i].lock = sem_open("/lock", O_CREAT | O_EXCL, 0666, 1);
        if (philos[i].lock == SEM_FAILED)
        {
            perror("sem_open failed");
            exit(EXIT_FAILURE);
        }
        
        sem_unlink("/lock");
        i++;
    }

}