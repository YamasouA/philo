/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:33:11 by asouta            #+#    #+#             */
/*   Updated: 2022/12/08 23:34:23 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	arg_num_check(int n)
{
	if (n < 5 || n > 6)
		return (false);
	return (true);
}

static bool	arg_val_check(int n, char **argv)
{
	int	cnt;

	cnt = 1;
	while (cnt < n)
	{
		if (!is_plus_number(argv[cnt]))
			return (false);
		cnt++;
	}
	return (true);
}

bool	argcheck(int n, char **argv)
{
	if (!arg_num_check(n))
		return (false);
	if (!arg_val_check(n, argv))
		return (false);
	return (true);
}
