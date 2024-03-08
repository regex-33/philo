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

void	handle_waitpid_error(void)
{
	if (errno == ECHILD)
		return ;
	else
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

void	break_cleanup(t_philo *philos, int num_of_philosophers)
{
	int	i;

	i = 0;
	cleanup(philos, num_of_philosophers);
	while (i < num_of_philosophers)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
	free(philos);
}

void	wait_and_cleanup(t_philo *philos, int num_of_philosophers)
{
	int		status;
	pid_t	pid;
	int		num_processes_remaining;

	num_processes_remaining = num_of_philosophers;
	while (num_processes_remaining > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			handle_waitpid_error();
			break ;
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		{
			break_cleanup(philos, num_of_philosophers);
			exit(0);
		}
		num_processes_remaining--;
	}
	cleanup(philos, num_of_philosophers);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_time	data;
	t_philo	*philos;

	if (!check_and_parse_arguments(argc, &data, argv))
		return (1);
	philos = malloc(sizeof(t_philo) * data.num_of_philosophers);
	if (!philos)
		return (1);
	init_philosophers(&data, philos, data.num_of_philosophers);
	create_processes(philos, data.num_of_philosophers);
	wait_and_cleanup(philos, data.num_of_philosophers);
	return (0);
}
/*
void	wait_and_cleanup(t_philo *philos, int num_of_philosophers)
{
	int		status;
	pid_t	pid;
	int		i;
	int		num_processes_remaining;

	num_processes_remaining = num_of_philosophers;
	while (num_processes_remaining > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			if (errno == ECHILD)
				break ;
			else
			{
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
}*/