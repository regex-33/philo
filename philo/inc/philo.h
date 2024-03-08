/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:04:38 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/08 10:04:39 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_time
{
	int				num_of_phils;
	int				die;
	pthread_mutex_t	died;
	int				eat;
	int				sleep;
	long long		start_time;
	int				do_right;
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
	long long		last_meal;
	t_time			*data;
	int				is_dead;
	int				num_of_times_to_eat;
	int				count;
	int				checker;
}					t_philosopher;

/*		do routine functions		*/

int					if_die(t_philosopher *philo);
int					check_for_philosopher_death(t_philosopher *philosophers,
						int num_philo);
void				*check_time_of_threads(void *arg);
void				execute_philosopher_actions(t_philosopher *philo,
						int philo_id, pthread_mutex_t *left_fork,
						pthread_mutex_t *right_fork);
void				*philosopher_thread(void *arg);

/*		parising functoins		*/

long long			ft_atoi(const char *str);
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
void				print_status(long timestamp, int id, char *msg);
void				log_state_change(int philosopher_id, const char *state,
						long long timestamp, long long first_time);

#endif
