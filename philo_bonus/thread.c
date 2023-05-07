/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:27:35 by nrgn              #+#    #+#             */
/*   Updated: 2023/05/07 14:10:47 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_data *data, int id, char *s)
{
	pthread_mutex_lock(&data->write);
	printf("%lld %d %s", ft_get_time() - data->start_time, id + 1, s);
	if (*s != 'd')
		pthread_mutex_unlock(&data->write);
}

static void	thinking(t_philo *philo)
{
	print_status(philo->data, philo->id, "is thinking\n");
}

static void	sleeping(t_philo *philo)
{
	long long int	clock;

	clock = ft_get_time();
	print_status(philo->data, philo->id, "is sleeping\n");
	usleep(philo->data->tsleep * 1000 - 16000);
	while (ft_get_time() - clock < philo->data->tsleep)
		continue ;
}

static void    diner_ready(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork_left]);
	print_status(philo->data, philo->id, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->fork_right]);
	print_status(philo->data, philo->id, "has taken a fork\n");
	pthread_mutex_lock(&philo->eating);
	print_status(philo->data, philo->id, "is eating\n");
	philo->last_eat = ft_get_time();
	philo->is_eating = 1;
	usleep(philo->data->teat * 1000 - 16000);
	while (ft_get_time() - philo->last_eat < philo->data->teat)
		continue ;
	philo->nb_meals++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_right]);
}


void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// if (philo->id % 2)
	// 	usleep(70);
	while (philo->data->loop)
	{
		diner_ready(philo);
		sleeping(philo);
		thinking(philo);
		usleep(100);
	}
	return (NULL);
}

