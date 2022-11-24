#include "philo.h"

void	print_stamp()
{

}

void	simulate(void *arg)
{
	//t_config	*config;
	t_philo	*philo;

	//config = (t_config *)arg;
	philo = (t_philo *)arg;
	printf("philo->id %d\n", philo->id);
	//pthread_mutex_lock();
	//pthread_mutex_unlock();
}

bool	create_thread(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		if (pthread_create(&config->philo[n].thread, NULL, (void *)simulate, &config->philo[n]))
			return (false);
		printf("create %zu thread\n", n);
		n++;
	}
	return (true);
}

bool	wait_thread(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		if (pthread_join(config->philo[n].thread, NULL))
			return (false);
		printf("finish %zu thread\n", n);
		n++;
	}
	return (true);
}

bool	start_simulation(t_config *config)
{
	bool	ret;

	ret = create_thread(config);
	if (!ret)
		return (false);
	ret = wait_thread(config);
	return (ret);
}
