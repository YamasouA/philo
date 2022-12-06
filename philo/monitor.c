#include "philo.h"

void	monitor(void *p)
{
	t_philo		*philo;
	long long	now;
	int			flag;

	philo = (t_philo *)p;
	flag = 0;
	while (1)
	{
		usleep(300);
		pthread_mutex_lock(&philo->config->monitor);
		if (philo->config->is_die)
		{
			pthread_mutex_unlock(&philo->config->monitor);
			break ;
		}
		pthread_mutex_unlock(&philo->config->monitor);
		pthread_mutex_lock(&philo->monitor_last);
		now = get_time();
		if (now == -1)
		{
			set_err(philo, "get_time error");
			pthread_mutex_unlock(&philo->monitor_last);
			break ;
		}
		if (now - philo->last_eat > philo->config->die)
		{
			philo->is_deth = true;
			flag = DIE;
		}
		pthread_mutex_unlock(&philo->monitor_last);
		if (flag != 0)
		{
			print_stamp(philo, flag);
			break ;
		}
	}
}

