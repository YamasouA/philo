#include "philo.h"

void	mutex_destroy(t_config *config)
{
	size_t	n;

	n = 0;
	pthread_mutex_destroy(&config->monitor);
	pthread_mutex_destroy(&config->print);
	while (n < config->num)
	{
		pthread_mutex_destroy(&config->forks[n]);
		pthread_mutex_destroy(&config->philo[n].monitor_die);
		pthread_mutex_destroy(&config->philo[n].monitor_last);
		n++;
	}
}
