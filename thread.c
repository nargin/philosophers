/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrgn <nrgn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:27:35 by nrgn              #+#    #+#             */
/*   Updated: 2023/05/05 14:51:04 by nrgn             ###   ########.fr       */
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

void    *post_mortem(void *data)
{
    t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->data->loop)
	{
		if (!philo->is_eating &&
			ft_get_time() - philo->last_eat >= philo->data->tdie)
		{
			pthread_mutex_lock(&philo->eating);
			print_status(philo->data, philo->id, "died\n");
			philo->data->is_dead = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		if (philo->data->philos[philo->data->n_philo - 1]->nb_meals
			== philo->skateboard->nb_eat)
			philo->data->loop = 0;
		usleep(100);
	}
	return (NULL);
}

void    diner_ready(t_philo *philo)
{
    pthread_mutex_lock(&philo->skateboard->forks[philo->left]);
    print_status(philo->skateboard, philo->id, "has taken a fork\n");
    pthread_mutex_lock(&philo->skateboard->forks[philo->right]);
    print_status(philo->skateboard, philo->id, "has taken a fork\n");
    pthread_mutex_lock(&philo->eating);
    print_status(philo->skateboard, philo->id, "is eating\n");
    philo->last_eat = ft_get_time();
    philo->is_eating = 1;
    usleep(philo->skateboard->time_to_eat * 1000 - 16000);
    while (ft_get_time() - philo->last_eat < philo->skateboard->time_to_eat)
        continue ;
    philo->nb_eat++;
    pthread_mutex_unlock(&philo->eating);
    pthread_mutex_unlock(&philo->skateboard->forks[philo->left]);
    pthread_mutex_unlock(&philo->skateboard->forks[philo->right]);
}

void	*philo_life(void *data)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)data;
	while (!philo->skateboard->is_dead)
	{
		diner_ready(philo);
		print_status(philo->skateboard, philo->id, "is sleeping\n");
		time = ft_get_time();
		usleep(philo->skateboard->time_to_sleep * 1000 - 16000);
		while (ft_get_time() - time < philo->skateboard->time_to_sleep)
			continue ;
		print_status(philo->skateboard, philo->id, "is thinking\n");
		usleep(100);
	}
	return (NULL);
}

