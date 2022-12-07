#include "philo.h"

void	free_all(t_config *config)
{
	free(config->philo);
	free(config->forks);
	free(config);
}
// arg: number_of_philo, time_to_die, time_to_eat,
//      time_to_sleep, [number_of_times_each_philosopher_must_eat]

int	main(int argc, char **argv)
{
	t_config	*config;

	if (!argcheck(argc, argv))
	{
		printf("arg is invalid\n");
		return (1);
	}
	config = init(argc, argv);
	if (config == NULL)
		return (1);
	start_simulation(config);
	mutex_destroy(config);
	free_all(config);
	return (0);
}
