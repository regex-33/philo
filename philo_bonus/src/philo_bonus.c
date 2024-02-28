#include "../inc/philo_bonus.h"

int is_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0;
        i++;
    }
    return (1);
}

int check_parameters(t_time *data, char **argv)
{
    int     i;

    i = 0;
    while (argv[i])
    {
        if (!is_number(argv[i]))
            return (0);
        if (i == 0)
            data->num_of_philosophers = ft_atoi(argv[i]);
        else if (i == 1)
            data->time_to_die = ft_atoi(argv[i]);
        else if (i == 2)
            data->time_to_eat = ft_atoi(argv[i]);
        else
            data->time_to_sleep = ft_atoi(argv[i]);
        i++;
    }
    return 1;
}
int main(int argc, char **argv)
{
    t_time  data;
    int     num_of_times_to_eat;
    if (argc < 5 || argc > 6)
    {
        printf("Error: Wrong number of arguments\n");
        return (1);
    }
	argv++;
	if (!check_parameters(&data, argv))
	{
		printf("error\n");
		return (1);
	}
    if (argc == 6)
    {
        if (!is_number(argv[4]))
            return (0);
        num_of_times_to_eat = ft_atoi(argv[4]);
    }
    //data.start_time = current_time_millis(0);
    data.start_time = get_time();
    
    t_philo philos[data.num_of_philosophers];
    init_philosophers(&data, philos, data.num_of_philosophers, num_of_times_to_eat);

    create_processes(philos, data.num_of_philosophers);

    int i = 0;
    while (i < data.num_of_philosophers)
    {
        waitpid(philos[i].pid, NULL, 0);
        i++;
    }
    cleanup(philos, data.num_of_philosophers);

    return (0);
}
