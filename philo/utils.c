#include "philo.h"

void	set_err(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->config->monitor);
	printf("%s\n", msg);
	philo->config->is_die = true;
	pthread_mutex_unlock(&philo->config->monitor);
}

long long	get_time()
{
	struct timeval	tv;
	long long	time;

	time = gettimeofday(&tv, NULL);
	if (time == -1)
		return (time);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

void	print_stamp(t_philo *philo, int type)
{
	long long	now;
	long long	diff;

	pthread_mutex_lock(&philo->config->print);
	now = get_time();
	if (now == -1)
	{
		// ERROR
	}
	diff = now - philo->config->start;
	if (!philo->config->is_die)
	{
		if (type == FORK)
			printf("%lld %d has taken a fork\n", diff, philo->id + 1);
		else if (type == EAT)
			printf("%lld %d is eating\n", diff, philo->id + 1);
		else if (type == SLEEP)
			printf("%lld %d is sleeping\n", diff, philo->id + 1);
		else if (type == THINK)
			printf("%lld %d is thinking\n", diff, philo->id + 1);
		else if (type == DIE)
		{
			pthread_mutex_lock(&philo->config->monitor);
			philo->config->is_die = true;
			pthread_mutex_unlock(&philo->config->monitor);
			printf("%lld %d died\n", diff, philo->id + 1);
		}
	}
	pthread_mutex_unlock(&philo->config->print);
}
