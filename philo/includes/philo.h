/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouta <asouta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:35:06 by asouta            #+#    #+#             */
/*   Updated: 2022/12/08 23:35:09 by asouta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# define EAT	1
# define FORK 2
# define SLEEP 3
# define THINK 4
# define DIE	5

typedef struct s_config	t_config;
typedef struct s_philo	t_philo;
struct s_config
{
	size_t			num;
	int				die;
	int				eat;
	int				sleep;
	int				end_time;
	long long		start;
	bool			is_die;
	bool			err;
	pthread_mutex_t	monitor;
	pthread_mutex_t	print;

	pthread_mutex_t	*forks;
	t_philo			*philo;
};

struct s_philo
{
	int				id;
	long long		last_eat;
	bool			is_deth;
	pthread_t		thread;
	pthread_mutex_t	monitor_last;
	pthread_mutex_t	monitor_die;
	t_config		*config;
};

// routine.c
void		start_routine(t_philo *philo);
void		philo_one(t_config *config);

// atoi.c
int			ft_atoi(const char *str);
bool		is_plus_number(const char *nbr);

// arg_utils.c
t_config	*init(int n, char **argv);
bool		argcheck(int n, char **argv);

// simulate.c
void		start_simulation(t_config *config);

// monitor.c
void		monitor(void *p);

// utils.c
long long	get_time(void);
void		print_stamp(t_philo *philo, int type);
void		set_err(t_philo *philo, char *msg);

// eat.c
void		eat(t_philo *philo);

// sleep.c
void		_sleep(long long wait_time);
void		do_sleep(t_philo *philo);

// destroy.c
void		mutex_destroy(t_config *config);
#endif
