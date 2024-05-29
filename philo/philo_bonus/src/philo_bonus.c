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

void	cleanup(t_philo *philos, int num_of_philosophers)
{
	int	i;

	i = 0;
	while (i < num_of_philosophers)
	{
		sem_close(philos[i].race_data);
		i++;
	}
	sem_close(philos[0].forks);
	sem_close(philos[0].data->lock_died);
}

int	check_and_parse_arguments(int argc, t_time *data, char **argv)
{
	int	result;

	result = 0;
	if (argc < 5 || argc > 6)
		return (ft_putendl_fd("Error: Wrong number of arguments", 2), 0);
	argv++;
	result = check_parameters(data, argv, 0);
	if (result == -1)
		return (ft_putendl_fd("philo: parse error", 2), 0);
	else if (!result)
		return (0);
	return (1);
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
			if (errno == ECHILD)
				return ;
			else
				return (perror("philo"), exit(EXIT_FAILURE));
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
			return (break_cleanup(philos, num_of_philosophers),
				exit(EXIT_SUCCESS));
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
	{
		if (data.num_of_times_to_eat <= 0)
			return (0);
		return (1);
	}
	philos = malloc(sizeof(t_philo) * data.num_of_philosophers);
	if (!philos)
		return (1);
	init_philosophers(&data, philos, data.num_of_philosophers);
	create_processes(philos, data.num_of_philosophers);
	wait_and_cleanup(philos, data.num_of_philosophers);
	return (0);
}
