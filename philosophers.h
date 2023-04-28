#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

# define MAX 2147483647
# define MIN -2147483648
# define ARG_ERR "number_of_philosophers \
time_to_die \
time_to_eat \
time_to_sleep \
{number_of_times_each_philosopher_must_eat}\n"

# define ARG_TOO_LOW "Error: Arguments under 60 or too high\n"

typedef struct s_philo {
	long 			start_time;
	long 			last_eat;
	int 			id;
	int 			is_eating;
	int 			nb_philo;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			nb_eat;
	int 			is_dead;
	pthread_t		thread;
	pthread_mutex_t	*forks;
}	t_philo;

// utils.c
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
int		ft_error(char *str);
long	ft_get_time(void);

#endif