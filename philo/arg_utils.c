#include "philo.h"

static bool	arg_num_check(int n)
{
	if (n < 4 || n > 6)
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
