#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_time
{
	int				    num_of_philosophers;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
    long                start_time;
}					t_time;

typedef struct  s_philo
{
    long            last_meal;
    struct s_time   *data;

    pid_t           pid;
    sem_t           *forks;
    sem_t           *lock;

    int             id;
    int             num_of_meals;
    int             num_of_times_to_eat;
    int             check_flag;
}               t_philo;

int     ft_atoi(const char *str);
long long	current_time_millis(long long first_time);
void    ft_usleep(useconds_t time);
void    print_status(long timestamp, int id, char *msg);
long    get_time(void);
void    init_philosophers(t_time *data, t_philo *philos, int num_of_philosophers, int num_of_times_to_eat);
void    create_processes(t_philo *philos, int num_of_philosophers);
void    *death_check_routine(void *philosopher);
void    take_forks(t_philo *philo);
void    put_forks(t_philo *philo);
void    philosopher_process(t_philo *philo);
void    cleanup(t_philo *philos, int num_of_philosophers);

#endif
