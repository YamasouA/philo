/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:33:48 by asouta            #+#    #+#             */
/*   Updated: 2022/12/08 23:34:13 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_one(t_config *config)
{
	print_stamp(&config->philo[0], FORK);
	_sleep(config->die);
	print_stamp(&config->philo[0], DIE);
}

void	start_routine(t_philo *philo)
{
	int	cnt;

	cnt = 0;
	while (1)
	{
		eat(philo);
		cnt++;
		pthread_mutex_lock(&philo->config->monitor);
		if (philo->config->is_die || \
			(philo->config->end_time != -1 && cnt >= philo->config->end_time))
		{
			pthread_mutex_unlock(&philo->config->monitor);
			break ;
		}
		pthread_mutex_unlock(&philo->config->monitor);
		do_sleep(philo);
		pthread_mutex_lock(&philo->config->monitor);
		if (philo->config->is_die)
		{
			pthread_mutex_unlock(&philo->config->monitor);
			break ;
		}
		pthread_mutex_unlock(&philo->config->monitor);
		print_stamp(philo, THINK);
	}
}
