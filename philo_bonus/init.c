/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:36:30 by romaurel          #+#    #+#             */
/*   Updated: 2023/05/07 16:09:30 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	**set_var(t_data *game)
{
	t_philo	**philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo *) * game->n_philo + 1);
	if (!philo)
		return (NULL);
	while (++i < game->n_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		if (pthread_mutex_init(&philo[i]->eating, NULL) != 0)
			return (NULL);
		philo[i]->data = game;
		philo[i]->id = i;
		philo[i]->is_eating = 0;
		philo[i]->nb_meals = 0;
		philo[i]->fork_left = i;
		philo[i]->fork_right = (i + 1) % philo[i]->data->n_philo;
	}
	return (philo);
}

static pthread_mutex_t	*ft_init_forks(int total)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * total);
	if (!forks)
		return (NULL);
	while (++i < total)
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (NULL);
	return (forks);
}

t_data	*ft_init(char *av[])
{
	t_data	*game;

	game = malloc(sizeof(t_data) * 1);
	if (!game)
		return (NULL);
	game->loop = 1;
	game->n_philo = ft_atoi(av[1]);
	game->tdie = ft_atoi(av[2]);
	game->teat = ft_atoi(av[3]);
	game->tsleep = ft_atoi(av[4]);
	game->n_meal = -1;
	if (av[5])
		game->n_meal = ft_atoi(av[5]);
	game->forks = ft_init_forks(game->n_philo);
	if (!game->forks)
		return (NULL);
	game->philos = set_var(game);
	if (!game->philos)
		return (NULL);
	if (pthread_mutex_init(&game->write, NULL) != 0)
		return (NULL);
	return (game);
}
