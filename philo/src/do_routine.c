void odd_philosopher_action(t_philosopher *philo, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
    if (if_die(philo))
        return;

    pthread_mutex_lock(left_fork);
    if (if_die(philo))
        return;
    print_status(get_time() - philo->data->start_time, philo->id, "has taken a fork");
    pthread_mutex_lock(right_fork);
    if (if_die(philo))
        return;
    print_status(get_time() - philo->data->start_time, philo->id, "has taken a fork");
}

void even_philosopher_action(t_philosopher *philo, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
    usleep(500);
    if (if_die(philo))
        return;
    pthread_mutex_lock(right_fork);
    if (if_die(philo))
        return;
    print_status(get_time() - philo->data->start_time, philo->id, "has taken a fork");
    pthread_mutex_lock(left_fork);
    if (if_die(philo))
        return;
    print_status(get_time() - philo->data->start_time, philo->id, "has taken a fork");
}

void philo_action_after_eating(t_philosopher *philo, int philo_id)
{
    print_status(get_time() - philo->data->start_time, philo_id, "is eating");
    usleep(philo->data->eat * 1000);
    philo->last_meal = get_time();
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void philo_action_after_sleeping(t_philosopher *philo, int philo_id)
{
    print_status(get_time() - philo->data->start_time, philo_id, "is sleeping");
    usleep(philo->data->sleep * 1000);
}

int philo_action_after_thinking(t_philosopher *philo, int philo_id)
{
    print_status(get_time() - philo->data->start_time, philo_id, "is thinking");
    if (philo->checker)
    {
        philo->count++;
        if (philo->count >= philo->num_of_times_to_eat)
            return 0;
    }
    return 1;
}
void *philosopher_thread(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    int philo_id = philo->id;
    pthread_mutex_t *left_fork = philo->left_fork;
    pthread_mutex_t *right_fork = philo->right_fork;

    while (1)
    {
        if (philo_id % 2)
            odd_philosopher_action(philo, left_fork, right_fork);
        else
            even_philosopher_action(philo, left_fork, right_fork);
        if (if_die(philo))
            return NULL;
        philo_action_after_eating(philo, philo_id);
        if (if_die(philo))
            return NULL;
        philo_action_after_sleeping(philo, philo_id);
        if (if_die(philo))
            return NULL;
        if (!philo_action_after_thinking(philo, philo_id))
            return NULL;
    }
    return NULL;
}