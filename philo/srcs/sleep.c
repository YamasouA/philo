/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:33:58 by asouta            #+#    #+#             */
/*   Updated: 2022/12/08 23:34:11 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
