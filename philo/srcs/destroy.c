/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:33:22 by asouta            #+#    #+#             */
/*   Updated: 2022/12/08 23:34:20 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy(t_config *config)
{
	size_t	n;

	n = 0;
	pthread_mutex_destroy(&config->monitor);
	pthread_mutex_destroy(&config->print);
	while (n < config->num)
	{
		pthread_mutex_destroy(&config->forks[n]);
		pthread_mutex_destroy(&config->philo[n].monitor_die);
		pthread_mutex_destroy(&config->philo[n].monitor_last);
		n++;
	}
}
