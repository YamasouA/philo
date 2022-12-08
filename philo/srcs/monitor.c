/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:33:43 by asouta            #+#    #+#             */
/*   Updated: 2022/12/08 23:34:15 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_someone_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->monitor);
	if (philo->config->is_die)
	{
		pthread_mutex_unlock(&philo->config->monitor);
		return (true);
	}
	pthread_mutex_unlock(&philo->config->monitor);
	return (false);
}

void	monitor(void *p)
{
	t_philo		*philo;
	long long	now;

	philo = (t_philo *)p;
	while (1)
	{
		usleep(300);
		if (is_someone_die(philo))
			break ;
		pthread_mutex_lock(&philo->monitor_last);
		now = get_time();
		if (now == -1)
			set_err(philo, "get_time error");
		if (now - philo->last_eat > philo->config->die)
		{
			philo->is_deth = true;
			pthread_mutex_unlock(&philo->monitor_last);
			print_stamp(philo, DIE);
			break ;
		}
		pthread_mutex_unlock(&philo->monitor_last);
	}
}
