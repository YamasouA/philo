/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:33:53 by asouta            #+#    #+#             */
/*   Updated: 2022/12/08 23:34:12 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	simulate(void *arg)
{
	t_philo		*philo;
	pthread_t	th_monitor;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->monitor_last);
	philo->last_eat = get_time();
	if (philo->last_eat == -1)
	{
		set_err(philo, "get_time error\n");
		pthread_mutex_unlock(&philo->monitor_last);
		return ;
	}
	pthread_mutex_unlock(&philo->monitor_last);
	if (pthread_create(&th_monitor, NULL, (void *)monitor, philo))
	{
		set_err(philo, "pthread_create error");
		return ;
	}
	if (philo->id % 2 != 0)
		usleep(500);
	start_routine(philo);
	pthread_join(th_monitor, NULL);
}

static size_t	create_thread(t_config *config)
{
	size_t	n;

	n = 0;
	while (n < config->num)
	{
		if (pthread_create(&config->philo[n].thread, NULL, \
			(void *)simulate, &config->philo[n]))
		{
			set_err(&config->philo[n], "pthread_create error");
			return (n);
		}
		n++;
	}
	return (n);
}

static bool	wait_thread(t_config *config, size_t n)
{
	while (n > 0)
	{
		n--;
		if (pthread_join(config->philo[n].thread, NULL))
			printf("%zu pthread_join is error\n", n);
	}
	return (true);
}

void	start_simulation(t_config *config)
{
	size_t	n;

	if (config->num == 1)
		return (philo_one(config));
	n = create_thread(config);
	wait_thread(config, n);
}
