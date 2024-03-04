/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:20:02 by yachtata          #+#    #+#             */
/*   Updated: 2024/03/03 09:20:03 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	check_and_parse_arguments(int argc, t_time *data, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	argv++;
	if (!check_parameters(data, argv))
	{
		printf("error\n");
		return (0);
	}
	return (1);
}

/*
void	wait_and_cleanup(t_philo *philos, int num_of_philosophers)
{
    int     status;
    pid_t   pid;
    int     i;

	while (num_of_philosophers > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		{
			i = 0;
			cleanup(philos, num_of_philosophers);
			while (i < num_of_philosophers)
			{
				kill(philos[i].pid, SIGKILL);
				i++;
			}
			exit(0);
		}
	}
	cleanup(philos, num_of_philosophers);
}*/

void	wait_and_cleanup(t_philo *philos, int num_of_philosophers)
{
    int     status;
    pid_t   pid;
    int     i;
    int     num_processes_remaining;
    
    num_processes_remaining = num_of_philosophers;
	while (num_processes_remaining > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			if (errno == ECHILD) {
                // No child processes left to wait for
                break;
            } else {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		{
			i = 0;
			cleanup(philos, num_of_philosophers);
			while (i < num_of_philosophers)
			{
				kill(philos[i].pid, SIGKILL);
				i++;
			}
			exit(0);
		}
		num_processes_remaining--;
	}
	cleanup(philos, num_of_philosophers);
}


int	main(int argc, char **argv)
{
	t_time	data;

	if (!check_and_parse_arguments(argc, &data, argv))
		return (1);
	// if (!get_num_of_times_to_eat(argc, argv, &num_of_times_to_eat))
	// 	return (1);
	//data.num_of_times_to_eat = num_of_times_to_eat;
    // printf("num : %s | die : %s | eat : %s | sleep : %s | num of time : %s\n", argv[1], argv[2], argv[3], argv[4], argv[5]);
    // printf("num : %d | die : %ld | eat : %ld | sleep : %ld | num of time : %ld\n", data.num_of_philosophers, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.num_of_times_to_eat);
	t_philo philos[data.num_of_philosophers];                  
	init_philosophers(&data, philos, data.num_of_philosophers);
	create_processes(philos, data.num_of_philosophers);
	wait_and_cleanup(philos, data.num_of_philosophers);
	return (0);
}

