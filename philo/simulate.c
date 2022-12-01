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

	now = get_time();
	if (now == -1)
		// ERROR
	pthread_mutex_lock(&philo->monitor);
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
	}
	pthread_mutex_unlock(&philo->monitor);
}

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
	_sleep(philo->config->eat);
	pthread_mutex_lock(&philo->monitor);
	print_stamp(philo, EAT);
	philo->total_eat += philo->config->eat;
	//printf("\x1b[31mphilo %d total_eat %d\x1b[0m\n", philo->id, philo->total_eat);
	if (philo->config->end_time != -1 && philo->total_eat > philo->config->end_time)
	{
		printf("\x1b[31mphilo %d over total_eat\x1b[0m\n", philo->id);
	}
	philo->last_eat = get_time();
	if (philo->last_eat == -1)
	{
		// ERROR
	}
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
	print_stamp(philo, FORK);
	pthread_mutex_lock(&philo->config->forks[right]);
	print_stamp(philo, FORK);
	//printf("\x1b[34mphilo %d pick right fork[%d]\x1b[0m\n", philo->id, right);
	//printf("\x1b[34mphilo %d pick left fork[%d]\x1b[0m\n", philo->id, left);
	return (ret);
}

void	monitor(void *p)
{
	t_philo	*philo;
	long long	now;

	philo = (t_philo *)p;
	while (1)
	{
		if (philo->config->is_die)
			break;
		usleep(500);
		//printf("-----monitoring [%d]-----\n", philo->id);
		now = get_time();
		if (now == -1)
		{
			// ERROR
			printf("Error 1\n");
			break;
		}
		pthread_mutex_lock(&philo->monitor);
		if (now - philo->last_eat > philo->config->die) // 餓死
		{
			philo->is_deth = true;
			print_stamp(philo, DIE);
			//printf("philo %d Error 2\n", philo->id);
			break;
		}
		if (philo->config->end_time!= -1 && (philo->total_eat > philo->config->end_time)) // 満腹
		{
			printf("Error 3\n");
			break;
		}
		pthread_mutex_unlock(&philo->monitor);
	}
	pthread_mutex_unlock(&philo->monitor);
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
	{
	}
	pthread_detach(th_monitor);
	if (philo->id % 2 != 0)
		usleep(500);
	while (1)
	{
		eat(philo);
		if (philo->config->is_die)
			break;
		_sleep(philo->config->sleep);
		if (philo->config->is_die)
			break;
		print_stamp(philo, SLEEP);
		print_stamp(philo, THINK);
		//printf("\x1b[35mphilo %d sleep %d milisec\x1b[0m\n", philo->id, philo->config->sleep);
		//_think(philo->config->think);
		//break;
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
		//printf("\x1b[32m");
		//printf("create %zu thread\n", n);
		//printf("\x1b[0m");
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
		//printf("\x1b[31m");
		//printf("finish %zu thread\n", n);
		//printf("\x1b[0m");
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
