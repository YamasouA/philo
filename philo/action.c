#include "philo.h"

void	_sleep(long long wait_time)
{
	long long	end;
	long long	now;

	end = get_time();
	if (end == -1)
		// ERROR
		return;
	end += wait_time;
	while (1)
	{
		now = get_time();
		if (now == -1)
			// ERROR
			return ;
		if (now >= end)
			break;
		usleep(1000);
	}
}

bool	eating(t_philo	*philo)
{
	bool	ret;
	int		right;
	int		left;

	ret = true;
	left = philo->id;
	right = (philo->id + philo->config->num - 1) % philo->config->num;
	pthread_mutex_lock(&philo->config->monitor);
	if (philo->config->is_die)
	{
		pthread_mutex_unlock(&philo->config->monitor);
		pthread_mutex_unlock(&philo->config->forks[right]);
		pthread_mutex_unlock(&philo->config->forks[left]);
		return (ret);
	}
	pthread_mutex_unlock(&philo->config->monitor);
	_sleep(philo->config->eat);
	print_stamp(philo, EAT);
	pthread_mutex_lock(&philo->monitor);
	philo->total_eat += philo->config->eat;
	philo->last_eat = get_time();
	if (philo->last_eat == -1)
	{
		// ERROR
	}
	pthread_mutex_unlock(&philo->monitor);
	pthread_mutex_unlock(&philo->config->forks[right]);
	pthread_mutex_unlock(&philo->config->forks[left]);
	// printf("koko\n");
	return (ret);
}

bool	get_fork(t_philo *philo)
{
	bool	ret;
	int		right;
	int		left;

	ret = true;
	left = philo->id;
	right = (philo->id + philo->config->num - 1) % philo->config->num;
	pthread_mutex_lock(&philo->config->forks[left]);
	print_stamp(philo, FORK);
	pthread_mutex_lock(&philo->config->forks[right]);
	print_stamp(philo, FORK);
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
