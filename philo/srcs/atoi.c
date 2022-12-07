#include "philo.h"

static	int	space(const char *str)
{
	if (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		return (1);
	else
		return (0);
}

static bool	is_overflow(char c, int nbr)
{
	if ((INT_MIN + (c - '0')) / 10 <= nbr
		&& nbr <= (INT_MAX - (c - '0')) / 10)
		return (false);
	return (true);
}

bool	is_plus_number(const char *nbr)
{
	int	i;

	i = 0;
	while (*nbr != '\0')
	{
		if (*nbr < '0' || *nbr > '9')
			return (false);
		if (!is_overflow(*nbr, i))
			i = (*nbr - '0') + i * 10;
		else
			return (false);
		nbr++;
	}
	if (i == 0)
		return (false);
	return (true);
}

int	ft_atoi(const char *str)
{
	long	i;
	int		sign;

	i = 0;
	sign = 1;
	while (space(str))
		str++;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	while (*str >= '0' && *str <= '9')
	{
		if (!is_overflow(*str, i))
			i = sign * (*str - '0') + i * 10;
		else if (sign == 1)
			return ((int)LONG_MAX);
		else
			return ((int)LONG_MIN);
		str++;
	}
	return ((int)i);
}
