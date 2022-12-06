#include "philo.h"

void	simulate_init(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor_last);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->monitor_last);
}

void	start_routine(t_philo *philo)
{
	int	cnt;

	cnt = 0;
	while (1)
	{
		eat(philo);
		cnt++;
		if (philo->config->end_time != -1 && cnt >= philo->config->end_time)
			break;
		pthread_mutex_lock(&philo->config->monitor);
		if (philo->config->is_die)
		{
			pthread_mutex_unlock(&philo->config->monitor);
			break;
		}
		pthread_mutex_unlock(&philo->config->monitor);
		print_stamp(philo, SLEEP);
		_sleep(philo->config->sleep);
		pthread_mutex_lock(&philo->config->monitor);
		if (philo->config->is_die)
		{
			pthread_mutex_unlock(&philo->config->monitor);
			break;
		}
		pthread_mutex_unlock(&philo->config->monitor);
		print_stamp(philo, THINK);
	}
}

void	simulate(void *arg)
{
	t_philo	*philo;
	pthread_t	th_monitor;

	philo = (t_philo *)arg;
	simulate_init(philo);
	if (philo->last_eat == -1)
		return;
	if (pthread_create(&th_monitor, NULL, (void *)monitor, philo))
	{
		set_err(philo, "pthread_create error");
		return ;
	}
	pthread_detach(th_monitor);
	if (philo->id % 2 != 0)
		usleep(500);
	start_routine(philo);
}

size_t	create_thread(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		if (pthread_create(&config->philo[n].thread, NULL, (void *)simulate, &config->philo[n]))
		{
			set_err(&config->philo[n], "pthread_create error");
			return (n);
		}
		n++;
	}
	return (n);
}

bool	wait_thread(t_config *config, size_t n)
{

	while (n > 0)
	{
		n--;
		if (pthread_join(config->philo[n].thread, NULL))
			printf("%zu pthread_join is error\n", n);
	}
	return (true);
}

void	philo_one(t_config *config)
{
	print_stamp(&config->philo[0], FORK);
	_sleep(config->die);
	print_stamp(&config->philo[0], DIE);
}

void	start_simulation(t_config *config)
{
	size_t	n;

	if (config->num == 1)
		return (philo_one(config));
	n = create_thread(config);
	wait_thread(config, n);
}
