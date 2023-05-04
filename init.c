/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:36:30 by romaurel          #+#    #+#             */
/*   Updated: 2023/05/04 19:27:43 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	set_var(t_data **data)
{
	int		i;

	i = -1;
	while (++i < (*data)->n_philo)
	{
		(*data)->n_philo[i] = malloc(sizeof(t_philo));
		if (!(*data)->n_philo[i])
			return (-1);
		if (pthread_mutex_init(&(*data)->n_philo[i]->eating, NULL) != 0)
			return (-1);
		(*data)->n_philo[i]->data = *data;
		(*data)->n_philo[i]->id = i;
		(*data)->n_philo[i]->is_eating = 0;
		(*data)->n_philo[i]->nb_meals = 0;
		(*data)->n_philo[i]->fork_left = i;
		(*data)->n_philo[i]->fork_right = (i + 1) % (*data)->n_philo;
	}
	(*data)->n_philo[i] = NULL;
	return (0);
}

int	ft_init_forks(t_data **data)
{
	int				i;

	i = -1;
	while (++i < nb_philo)
		if (pthread_mutex_init(*data->forks[i], NULL) != 0)
			return (-1);
	return (0);
}

int	ft_init_arg(int ac, char *av[], t_data **data)
{
	*data->n_philo = ft_atoi(av[1]);
	if (check_value(*data->n_philo, 0) == -1)
		return (-1);
	*data->tdie = ft_atoi(av[2]);
	if (check_value(data->tdie, 1) == -1)
		return (-1);
	*data->teat = ft_atoi(av[3]);
	if (check_value(philo->teat, 2) == -1)
		return (-1);
	*data->tsleep = ft_atoi(av[4]);
	if (check_value(*data->tsleep, 3) == -1)
		return (-1);
	*data->n_meal = -1;
	if (ac == 6)
	{
		*data->n_meal = ft_atoi(av[5]);
		if (check_value(*data->n_meal, 4) == -1)
			return (-1);
	}
	*data->forks = malloc(sizeof(pthread_mutex_t) * (*data)->nb_philo);
	if (!(*data)->forks || ft_init_forks(data) == -1)
		return (-1);
	return (1);
}

int	ft_init(t_data **game, int ac, char *av[])
{
	*game = malloc(sizeof(t_data));
	if (!*game)
		return (ft_error(MALLOC_ERR));
	if (!ft_init_arg(ac, av, game) || set_var(game))
		return (-1);
	return (0);
}