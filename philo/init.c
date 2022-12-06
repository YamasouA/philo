#include "philo.h"

void	init_philo(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		config->philo[n].last_eat = 0;
		config->philo[n].id = n;
		config->philo[n].config = config;
		config->philo[n].is_deth = false;
		pthread_mutex_init(&config->philo[n].monitor_die, NULL);
		pthread_mutex_init(&config->philo[n].monitor_last, NULL);
		n++;
	}
}

void	init_pthread(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		pthread_mutex_init(&config->forks[n], NULL);
		n++;
	}
}

void	init_philo_and_fork(t_config *config)
{
	config->philo = malloc(sizeof(t_philo) * config->num);
	if (!config->philo)
	{
		free(config);
		config = NULL;
		return ;
	}
	config->forks = malloc(sizeof(pthread_mutex_t) * config->num);
	if (!config->forks)
	{
		free(config->philo);
		free(config);
		config = NULL;
		return ;
	}
	init_philo(config);
	init_pthread(config);
}

t_config	*init(int n, char **argv)
{
	t_config	*config;

	config = malloc(sizeof(t_config) * 1);
	if (config == NULL)
		return (NULL);
	config->is_die = false;
	pthread_mutex_init(&config->monitor, NULL);
	pthread_mutex_init(&config->print, NULL);
	config->num = ft_atoi(argv[1]);
	config->die = ft_atoi(argv[2]);
	config->eat = ft_atoi(argv[3]);
	config->sleep = ft_atoi(argv[4]);
	config->start = get_time();
	if (config->start == -1)
	{
		free(config);
		return (NULL);
	}
	if (n == 5)
		config->end_time = ft_atoi(argv[5]);
	else
		config->end_time = -1;
	init_philo_and_fork(config);
	return (config);
}
