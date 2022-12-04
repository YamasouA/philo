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
	//printf("diff: %lld\n", wait_time);
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
		return (ret);
	}
	pthread_mutex_unlock(&philo->config->monitor);
	_sleep(philo->config->eat);
	print_stamp(philo, EAT);
	pthread_mutex_lock(&philo->monitor);
	// pthread_mutex_lock(&philo->config->monitor);
	philo->total_eat += philo->config->eat;
	//printf("\x1b[31mphilo %d total_eat %d\x1b[0m\n", philo->id, philo->total_eat);
	// if (philo->config->end_time != -1 && philo->total_eat > philo->config->end_time)
	// {
	// 	printf("\x1b[31mphilo %d over total_eat\x1b[0m\n", philo->id);
	// }
	philo->last_eat = get_time();
	if (philo->last_eat == -1)
	{
		// ERROR
	}
	// pthread_mutex_unlock(&philo->config->monitor);
	pthread_mutex_unlock(&philo->monitor);
	pthread_mutex_unlock(&philo->config->forks[right]);
	pthread_mutex_unlock(&philo->config->forks[left]);
	//printf("\x1b[33mphilo %d put down right fork[%d]\x1b[0m\n", philo->id, right);
	//printf("\x1b[33mphilo %d put down left fork[%d]\x1b[0m\n", philo->id, left);
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
	//printf("left: %d\n", left);
	//printf("right: %d\n", right);
	pthread_mutex_lock(&philo->config->forks[left]);
	// pthread_mutex_lock(&philo->monitor);
	print_stamp(philo, FORK);
	pthread_mutex_lock(&philo->config->forks[right]);
	print_stamp(philo, FORK);
	// pthread_mutex_unlock(&philo->monitor);
	//printf("\x1b[34mphilo %d pick right fork[%d]\x1b[0m\n", philo->id, right);
	//printf("\x1b[34mphilo %d pick left fork[%d]\x1b[0m\n", philo->id, left);
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
