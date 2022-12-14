/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:33:28 by asouta            #+#    #+#             */
/*   Updated: 2022/12/11 23:03:08 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_unlock(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + philo->config->num - 1) % philo->config->num;
	pthread_mutex_unlock(&philo->config->forks[right]);
	pthread_mutex_unlock(&philo->config->forks[left]);
}

static void	fork_lock(t_philo *philo)
{
	int		right;
	int		left;
	int		min;
	int		max;

	left = philo->id;
	right = (philo->id + philo->config->num - 1) % philo->config->num;
	if (left < right)
	{
		min = left;
		max = right;
	}
	else
	{
		min = right;
		max = left;
	}
	pthread_mutex_lock(&philo->config->forks[min]);
	print_stamp(philo, FORK);
	pthread_mutex_lock(&philo->config->forks[max]);
	print_stamp(philo, FORK);
}

static void	eating(t_philo	*philo)
{
	print_stamp(philo, EAT);
	pthread_mutex_lock(&philo->monitor_last);
	philo->last_eat = get_time();
	if (philo->last_eat == -1)
		set_err(philo, "get_time error");
	pthread_mutex_unlock(&philo->monitor_last);
	wait_time(philo->config->eat);
}

void	eat(t_philo *philo)
{
	fork_lock(philo);
	eating(philo);
	fork_unlock(philo);
}
