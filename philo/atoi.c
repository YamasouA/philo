#include "philo.h"

static	int	space(const char *str)
{
	if (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		return (1);
	else
		return (0);
}

static	bool	is_overflow(const char str, long long i, int sign)
{
	if (sign > 0 && (LLONG_MAX - sign * (str - '0')) / 10 >= i)
		return (true);
	else if (sign < 0 && (LLONG_MIN - sign * (str - '0')) / 10 <= i)
		return (true);
	return (false);
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
		if (is_overflow(*str, i, sign))
			i = sign * (*str - '0') + i * 10;
		else if (sign == 1)
			return ((int)LONG_MAX);
		else
			return ((int)LONG_MIN);
		str++;
	}
	return ((int)i);
}
