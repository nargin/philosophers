/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day_in_a_life.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrgn <nrgn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:27:35 by nrgn              #+#    #+#             */
/*   Updated: 2023/04/30 12:47:32 by nrgn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_skateboard *big_s, int id, char *s)
{
	pthread_mutex_lock(&big_s->write);
	printf("%lld %d %s", ft_get_time() - big_s->start_time, id + 1, s);
	if (s[0] != 'd')
		pthread_mutex_unlock(&big_s->write);
}

void    *post_mortem(void *data)
{
    t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->skateboard->is_dead)
	{
		if (!philo->is_eating
			&& ft_get_time() - philo->last_eat >= philo->skateboard->time_to_die)
		{
			pthread_mutex_lock(&philo->eating);
			print_status(philo->skateboard, philo->id, "died\n");
			philo->skateboard->is_dead = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		if (philo->skateboard->philos[philo->skateboard->nb_philo - 1]->nb_eat
			== philo->skateboard->nb_eat)
			philo->skateboard->is_dead = 0;
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
	while (philo->skateboard->is_dead)
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

