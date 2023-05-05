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
# define MEALS "Error: number of time each philosopher must eat is too short\n"
# define MALLOC_ERR "Error: Malloc failed\n"
# define THREAD_ERR "Error: Thread failed\n"
# define ARG_TOO_LOW "Error: Arguments under 60 or too high\n"

typedef struct s_philo {
	int					fork_right;
	int					fork_left;
	int					is_eating;
	long long int		last_eat;
	pthread_t			th_philo;
	pthread_t			th_death;
	int					nb_meals;
	pthread_mutex_t		eating;
	int					id;
	struct s_data	*data;
}				t_philo;

typedef struct s_data {
	long long int	start_time;
	t_philo			**philos;
	int 			n_philo;
	pthread_mutex_t	*forks;
	int 			tsleep;
	int 			n_meal;
	pthread_mutex_t	 write;
	int 			loop;
	int 			tdie;
	int 			teat;
}					t_data;

int	ft_init(t_data **game, int ac, char *av[]);
void	print_struct(t_data *data);

// utils.c
int			check_value(int value, int order);
int			ft_atoi(const char *str);
int			ft_error(char *str);
long long	ft_get_time(void);

// thread.c
void	*start_routine(void *data);
void	*philo_life(void *data);
void    diner_ready(t_philo *philo);
void    *post_mortem(void *data);
void	print_status(t_data *data, int id, char *s);

#endif