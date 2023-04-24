#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo {
	int 			id;
	int 			nb_eat;
	int 			is_eating;
	long 			last_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_var_philo	*var;
}	t_philo;

typedef struct s_var_philo {
	int 			nb_philo;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			nb_eat;
	int 			is_dead;
	long 			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	t_philo			*philo;
}	t_var_philo;
#endif