#include "philo.h"

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

	pthread_mutex_lock(&philo->config->monitor);
	now = get_time();
	if (now == -1)
	{
		// ERROR
	}
	// pthread_mutex_lock(&philo->monitor);
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
			philo->config->is_die = true;
			printf("%lld %d died\n", diff, philo->id + 1);
		}
		else if (type == FULL)
		{
			philo->config->is_die = true;
			// printf("%lld %d ", diff, philo->id + 1);
		}
	}
	pthread_mutex_unlock(&philo->config->monitor);
	// pthread_mutex_unlock(&philo->monitor);
}