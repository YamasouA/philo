#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>

typedef struct s_philo	t_philo;
struct s_philo
{
	//int	id;
	//int	left_fork;
	//int	right_fork;
	int	id;
	int	eat_last;
	pthread_t	thread;
};


typedef struct s_config	t_config;
struct s_config
{
	size_t	num;
	int	die;
	int	eat;
	int	sleep;
	int	end_time;
	int	total_eat;

	pthread_mutex_t	*forks;
	t_philo	*philo;
};

// utils.c
int	ft_atoi(const char *str);

// arg_utils.c
t_config	*init(int n, char **argv);
bool	argcheck(int n);

// simulate.c
bool	start_simulation(t_config *config);
