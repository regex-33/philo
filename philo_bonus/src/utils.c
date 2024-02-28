#include "../inc/philo_bonus.h"

void take_forks(t_philo *philo)
{
    sem_wait(philo->forks);
    sem_wait(philo->forks);
}

void put_forks(t_philo *philo)
{
    sem_post(philo->forks);
    sem_post(philo->forks);
}

void ft_usleep(useconds_t time)
{
    struct timeval start;
    struct timeval current;

    gettimeofday(&start, NULL);
    while (1)
    {
        usleep(50);
        gettimeofday(&current, NULL);
        if ((current.tv_sec * 1000000 + current.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec) >= time)
            break;
    }
}

long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_status(long timestamp, int id, char *msg)
{
  //  printf("\n time %ld\n", timestamp);
    printf("%ld %d %s\n", timestamp, id, msg);
}

void cleanup(t_philo *philos, int num_of_philosophers)
{
    int i;

    i = 0;
    while(i < num_of_philosophers)
    {
        sem_close(philos[i].lock);
        i++;
    }
    sem_close(philos[0].forks);
}

