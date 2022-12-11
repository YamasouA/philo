/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:33:58 by asouta            #+#    #+#             */
/*   Updated: 2022/12/11 23:02:54 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_time(long long wait_time)
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
	wait_time(philo->config->sleep);
}
