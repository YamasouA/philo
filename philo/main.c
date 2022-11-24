#include "philo.h"

int main(int argc, char **argv)
{
	t_config	*config;

	if (!argcheck(argc))
		return (1);
	config = init(argc, argv);
	if (config == NULL)
		return (1);
	start_simulation(config);

	return (0);
}
