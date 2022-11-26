#include "philo.h"

void	print_stamp()
{

}

bool	eating(t_philo	*philo)
{
	bool	ret;
	int		right;
	int		left;

	ret = true;
	right = (philo->id + 1) % philo->config->num;
	if (philo->id == 0)
		left = philo->config->num - 1;
	else
		left = philo->id - 1;
	pthread_mutex_unlock(&philo->config->forks[right]);
	printf("\x1b[33mphilo %d put down right fork[%d]\x1b[0m\n", philo->id, right);
	pthread_mutex_unlock(&philo->config->forks[left]);
	printf("\x1b[33mphilo %d put down left fork[%d]\x1b[0m\n", philo->id, left);
	return (ret);
}

bool	get_fork(t_philo *philo)
{
	bool	ret;
	int		right;
	int		left;

	ret = true;
	right = (philo->id + 1) % philo->config->num;
	if (philo->id == 0)
		left = philo->config->num - 1;
	else
		left = philo->id - 1;
	pthread_mutex_lock(&philo->config->forks[left]);
	printf("\x1b[34mphilo %d pick left fork[%d]\x1b[0m\n", philo->id, left);
	pthread_mutex_lock(&philo->config->forks[right]);
	printf("\x1b[34mphilo %d pick right fork[%d]\x1b[0m\n", philo->id, right);
	return (ret);
}

bool	eat(t_philo *philo)
{
	bool	flag;
	flag = get_fork(philo);
	if (!flag)
		return (flag);
	flag = flag & eating(philo);
	return (flag);
}

void	simulate(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eat(philo);
		break;
		//sleep();
	}
}

bool	create_thread(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		if (pthread_create(&config->philo[n].thread, NULL, (void *)simulate, &config->philo[n]))
			return (false);
		printf("\x1b[32m");
		printf("create %zu thread\n", n);
		printf("\x1b[0m");
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
		printf("\x1b[31m");
		printf("finish %zu thread\n", n);
		printf("\x1b[0m");
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
