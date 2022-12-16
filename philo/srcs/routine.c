/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:33:48 by asouta            #+#    #+#             */
/*   Updated: 2022/12/16 00:57:40 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_one(t_config *config)
{
	print_stamp(&config->philo[0], FORK);
	wait_time(config->die);
	print_stamp(&config->philo[0], DIE);
}

void	philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor_die);
	philo->is_die = true;
	pthread_mutex_unlock(&philo->monitor_die);
	pthread_mutex_unlock(&philo->config->monitor);
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
			philo_full(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->config->monitor);
		do_sleep(philo);
		do_think(philo);
		/*
		pthread_mutex_lock(&philo->config->monitor);
		if (philo->config->is_die)
		{
			pthread_mutex_unlock(&philo->config->monitor);
			break ;
		}
		pthread_mutex_unlock(&philo->config->monitor);
		*/
	}
}
