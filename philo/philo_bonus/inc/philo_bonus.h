/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:23:09 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 19:08:07 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_time
{
	int				num_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	long			num_of_times_to_eat;
	sem_t			*lock_died;
}					t_time;

typedef struct s_philo
{
	long			last_meal;
	struct s_time	*data;

	pid_t			pid;
	sem_t			*forks;
	sem_t			*race_data;
	sem_t			*death_sem;

	int				id;
	int				num_of_meals;
	int				num_of_times_to_eat;
	int				check_flag;
}					t_philo;

/*		creat processes		*/

void				create_death_checker(pthread_t *death_checker,
						t_philo *philo);
void				perform_actions_while_eating(t_philo *philo);
void				perform_actions_while_sleeping(t_philo *philo);
void				philosopher_process(t_philo *philo);
void				create_processes(t_philo *philos, int num_of_philosophers);

/*		init_phiosophers	*/

void				*death_check_routine(void *philosopher);
void				initialize_forks(sem_t **forks, int num_of_philosophers);
void				initialize_philosopher(t_philo *philo, int id, t_time *data,
						sem_t *forks);
void				init_philosophers(t_time *data, t_philo *philos,
						int num_of_times_to_eat);

/*			parsing			*/

void				ft_putendl_fd(char *s, int fd);
long long			ft_atoi(const char *str);
int					is_number(char *str);
int					check_parameters(t_time *data, char **argv, int i);

/*		philo bonus			*/

void				cleanup(t_philo *philos, int num_of_philosophers);
int					check_and_parse_arguments(int argc, t_time *data,
						char **argv);
void				break_cleanup(t_philo *philos, int num_of_philosophers);
void				wait_and_cleanup(t_philo *philos, int num_of_philosophers);

/*			utils			*/

void				take_forks(t_philo *philo);
void				put_forks(t_philo *philo);
long				get_time(void);
void				print_status(long timestamp, int id, char *msg);
void				put_time_stamp_memset(long *last_meal);

#endif