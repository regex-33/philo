/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:12:11 by yachtata          #+#    #+#             */
/*   Updated: 2024/02/24 06:04:31 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

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
	int				eat;
	int				sleep;
	long long		start_time;
	int 			do_right;
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
}					t_philosopher;

void print_status(long timestamp, int id, char *msg);
long long	current_time_millis(long long first_time);
void	log_state_change(int philosopher_id, const char *state,
		long long timestamp, long long first_time);
void check_time_to_die(int id, long long first_time, t_philosopher *philo);
void				*ft_memset(void *b, int c, size_t len);
int					check_parameters(t_time *data, char **argv);
long long			ft_atoi(const char *str);
void init_mutex(pthread_mutex_t *forks, int num_of_phils);
void destroy_mutex(pthread_mutex_t *forks, int num_of_phils);
long get_time(void);
void wait_threads(t_philosopher *philosophers, int num_of_phils);

#endif
