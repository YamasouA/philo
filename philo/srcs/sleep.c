#include "philo.h"

void	_sleep(long long wait_time)
{
	long long	end;
	long long	now;

	end = get_time();
	if (end == -1)
	{
		printf("get_time error\n");
		return ;
	}
	end += wait_time;
	while (1)
	{
		now = get_time();
		if (now == -1)
		{
			printf("get_time error\n");
			return ;
		}
		if (now >= end)
			break ;
		usleep(1000);
	}
}

void	do_sleep(t_philo *philo)
{
	print_stamp(philo, SLEEP);
	_sleep(philo->config->sleep);
}
