#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>
#define EAT	1
#define FORK 2
#define SLEEP 3
#define THINK 4
#define DIE	5
#define FULL 6

typedef struct s_config	t_config;
typedef struct s_philo	t_philo;
struct s_config
{
	size_t	num;
	int	die; // time_to_die
	int	eat; // time_to_eat
	int	sleep; // time_to_sleep
	int	end_time; // must_eat_time
	long long	start;

	bool is_die;
	pthread_mutex_t	monitor;

	pthread_mutex_t	*forks;
	t_philo	*philo;
};

struct s_philo
{
	int	id;
	long long	last_eat;
	int	total_eat; // philo's eat total time
	bool	is_deth;
	pthread_t	thread;
	pthread_mutex_t	monitor;
	t_config	*config;
};

// atoi.c
int	ft_atoi(const char *str);

// arg_utils.c
t_config	*init(int n, char **argv);
bool	argcheck(int n);

// simulate.c
bool	start_simulation(t_config *config);
long long	get_time();

// utils.c
long long	get_time();
void	print_stamp(t_philo *philo, int type);

// action.c
bool	eat(t_philo *philo);
void	_sleep(long long wait_time);