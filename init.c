/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:36:30 by romaurel          #+#    #+#             */
/*   Updated: 2023/05/06 15:39:37 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	**set_var(t_data *game)
{
	t_philo	**philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo *) * game->n_philo);
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
		philo[i]->fork_right = (i + 1) % game->n_philo;
		philo[i]->last_eat = ft_get_time();
	}
	return (philo);
}

static int	ft_init_forks(t_data **data)
{
	int	i;

	i = -1;
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->n_philo);
	if (!(*data)->forks)
		return (-1);
	while (++i < (*data)->n_philo)
		if (pthread_mutex_init(&(*data)->forks[i], NULL) != 0)
			return (-1);
	if (pthread_mutex_init(&(*data)->write, NULL) != 0)
		return (-1);
	return (0);
}

static int	ft_init_arg(int ac, char *av[], t_data **data)
{
	(*data)->loop = 1;
	(*data)->n_philo = ft_atoi(av[1]);
	if (check_value((*data)->n_philo, 0) == -1)
		return (-1);
	(*data)->tdie = ft_atoi(av[2]);
	if (check_value((*data)->tdie, 1) == -1)
		return (-1);
	(*data)->teat = ft_atoi(av[3]);
	if (check_value((*data)->teat, 2) == -1)
		return (-1);
	(*data)->tsleep = ft_atoi(av[4]);
	if (check_value((*data)->tsleep, 3) == -1)
		return (-1);
	(*data)->n_meal = -1;
	if (ac == 6)
	{
		(*data)->n_meal = ft_atoi(av[5]);
		if (check_value((*data)->n_meal, 4) == -1)
			return (-1);
	}
	if (ft_init_forks(data) == -1)
		return (-1);
	return (1);
}

int	ft_init(t_data **game, int ac, char *av[])
{
	*game = malloc(sizeof(t_data));
	if (!*game)
		return (ft_error(MALLOC_ERR));
	if (!ft_init_arg(ac, av, game))
		return (-1);
	(*game)->philos = set_var((*game));
	if (!(*game)->philos)
		return (-1);
	return (0);
}