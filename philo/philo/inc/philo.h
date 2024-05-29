/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:04:38 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 19:17:55 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_time
{
	long			num_of_phils;
	long			die;
	pthread_mutex_t	died;
	long			eat;
	long			sleep;
	long			start_time;
	int				philosopher_died;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	last_meal_mutex;
	int				flag;
}					t_time;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	t_time			*data;
	int				is_dead;
	long			num_of_times_to_eat;
	int				count;
	int				checker;
}					t_philosopher;

/*		do routine functions		*/

int					if_die(t_philosopher *philo);
int					check_for_philosopher_death(t_philosopher *philosophers,
						int num_philo);
void				*check_time_of_threads(void *arg);
int					execute_philosopher_actions(t_philosopher *philo,
						int philo_id, pthread_mutex_t *left_fork,
						pthread_mutex_t *right_fork);
void				*philosopher_thread(void *arg);

/*		print function			*/

void				print_status(long timestamp, int id, char *msg);
long long			ft_atoi(const char *str);
void				ft_putendl_fd(char *s, int fd);

/*		parising functoins		*/

int					is_number(char *str);
int					check_parameters(t_time *data, char **argv);

/*		philo_actions functions		*/

void				odd_philosopher_action(t_philosopher *philo,
						pthread_mutex_t *left_fork,
						pthread_mutex_t *right_fork);
void				even_philosopher_action(t_philosopher *philo,
						pthread_mutex_t *left_fork,
						pthread_mutex_t *right_fork);
void				philo_action_after_eating(t_philosopher *philo,
						int philo_id);
void				philo_action_after_sleeping(t_philosopher *philo,
						int philo_id);
int					philo_action_after_thinking(t_philosopher *philo,
						int philo_id);

/*		main philo functions		*/

int					initialize_vars(t_time *data, int num_of_times_to_eat);
void				init_philosophers(t_time *data, pthread_mutex_t *forks,
						t_philosopher *philosophers, int num_of_times_to_eat);
void				destroy_mutexes(t_time *data, pthread_mutex_t *forks,
						int num_of_phils);
void				init_mutexes(t_time *data, pthread_mutex_t *forks,
						int num_of_phils);

/*		utils functions		*/

void				wait_threads(t_philosopher *philosophers, int num_of_phils);
long				get_time(void);
void				put_time_stamp_memset(long *last_meal);
void				ft_usleep(useconds_t time);
long				get_reamining_time(t_philosopher *philo, long time_action);
#endif
