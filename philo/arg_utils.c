#include "philo.h"

bool	argcheck(int n)
{
	if (n < 4 || n > 6)
		return (false);

	return (true);
}

void	init_philo(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		config->philo[n].last_eat = 0;
		config->philo[n].id = n;
		config->philo[n].config = config;
		config->philo[n].total_eat = 0;
		config->philo[n].is_deth = false;
		// mutex_initのエラー処理 ERROR
		pthread_mutex_init(&config->philo[n].monitor, NULL);
		n++;
	}
}

bool	init_pthread(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		if (pthread_mutex_init(&config->forks[n], NULL) == -1)
			return (false);
		n++;
	}
	return (true);
}

t_config	*init(int n, char **argv)
{
	t_config	*config;

	config = malloc(sizeof(t_config) * 1);
	if (config == NULL)
		return (NULL);
	config->is_die = false;
	config->num = ft_atoi(argv[1]);
	config->die = ft_atoi(argv[2]);
	config->eat = ft_atoi(argv[3]);
	config->sleep = ft_atoi(argv[4]);
	config->start = get_time();
	if (config->start == -1)
	{
		//ERROR
	}
	if (n > 5)
		config->end_time = ft_atoi(argv[5]);
	else
		config->end_time = -1;
	config->philo = malloc(sizeof(t_philo) * config->num);
	if (!config->philo)
	{
		free(config);
		return (NULL);
	}
	config->forks = malloc(sizeof(pthread_mutex_t) * config->num);
	if (!config->forks)
	{
		free(config->philo);
		free(config);
		return (NULL);
	}
	init_philo(config);
	if (!init_pthread(config))
	{
		free(config->philo);
		free(config->forks);
		free(config);
		return (NULL);
	}
	return (config);
}
