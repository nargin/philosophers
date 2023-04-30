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
	pthread_mutex_t		eating;
	pthread_t			thp;
	pthread_t			thd;
	int					id;
	int					left;
	int					right;
	int					nb_eat;
	int					is_eating;
	long long			last_eat;
	struct s_skateboard	*skateboard;
}				t_philo;

typedef struct s_skateboard {
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	long long int	start_time;
	int 			is_dead;
	int 			nb_philo;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			nb_eat;
}					t_skateboard;

// utils.c
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
int		ft_error(char *str);
long	ft_get_time(void);

// day_in_a_life.c
void	*start_routine(void *data);
void	*philo_life(void *data);
void    diner_ready(t_philo *philo);
void    *post_mortem(void *data);
void	print_status(t_skateboard *big_s, int id, char *s);

#endif