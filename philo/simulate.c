#include "philo.h"

void	monitor(void *p)
{
	t_philo	*philo;
	long long	now;
	int		flag;

	philo = (t_philo *)p;
	flag = 0;
	while (1)
	{
		usleep(300);
		// usleep(500);
		pthread_mutex_lock(&philo->config->monitor);
		if (philo->config->is_die)
		{
			pthread_mutex_unlock(&philo->config->monitor);
			break;
		}
		pthread_mutex_unlock(&philo->config->monitor);
		
		pthread_mutex_lock(&philo->monitor);
		now = get_time();
		if (now == -1)
		{
			// ERROR
			printf("Error 1\n");
			break;
		}
		// printf("philo->total_eat: %d", philo->total_eat);
		if (philo->config->end_time!= -1 && (philo->total_eat > philo->config->end_time)) // 満腹
		{
			// printf("Error 3\n");
			flag = FULL;
			philo->is_deth = true;
			pthread_mutex_unlock(&philo->monitor);
			break;
		}
		else if (now - philo->last_eat > philo->config->die) // 餓死
		{
			philo->is_deth = true;
			flag = DIE;
		}
		pthread_mutex_unlock(&philo->monitor);
		if (flag != 0)
		{
			print_stamp(philo, flag);
			break;
		}
	}
}

void	simulate(void *arg)
{
	t_philo	*philo;
	pthread_t	th_monitor;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->monitor);
	philo->last_eat = get_time();
	if (philo->last_eat == -1)
	{
		// ERROR
	}
	pthread_mutex_unlock(&philo->monitor);
	pthread_create(&th_monitor, NULL, (void *)monitor, philo);
	pthread_detach(th_monitor);
	if (philo->id % 2 != 0)
		usleep(500);
	while (1)
	{
		eat(philo);
		pthread_mutex_lock(&philo->config->monitor);
		// printf("hoga1\n");
		if (philo->config->is_die)
		{
			// printf("hoga2\n");
			pthread_mutex_unlock(&philo->config->monitor);
			break;
		}
		// printf("hoga\n");
		pthread_mutex_unlock(&philo->config->monitor);
		_sleep(philo->config->sleep);
		pthread_mutex_lock(&philo->config->monitor);
		// pthread_mutex_lock(&philo->monitor);
		if (philo->config->is_die)
		{
			pthread_mutex_unlock(&philo->config->monitor);
			break;
		}
		// pthread_mutex_unlock(&philo->monitor);
		pthread_mutex_unlock(&philo->config->monitor);
		print_stamp(philo, SLEEP);
		print_stamp(philo, THINK);
	}
}

bool	create_thread(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		if (pthread_create(&config->philo[n].thread, NULL, (void *)simulate, &config->philo[n]))
		{
			return (false);
		}
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
		n++;
	}
	return (true);
}

bool	philo_one(t_config *config)
{
	print_stamp(&config->philo[0], FORK);
	_sleep(config->die);
	print_stamp(&config->philo[0], DIE);
	return (true);
}

bool	start_simulation(t_config *config)
{
	bool	ret;

	if (config->num == 1)
		return (philo_one(config));
	ret = create_thread(config);
	if (!ret)
		return (false);
	ret = wait_thread(config);
	return (ret);
}
