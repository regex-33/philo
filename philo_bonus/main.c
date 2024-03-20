#include "inc/philo_bonus.h"

int main()
{
		sem_unlink("/lock");
		sem_unlink("/race_data");
		sem_unlink("/print_lock");
        return 0;
}