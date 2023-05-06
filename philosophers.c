/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:20:23 by nrgn              #+#    #+#             */
/*   Updated: 2023/05/06 15:55:06 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_game(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_detach(data->philos[i]->th_philo);
		pthread_detach(data->philos[i]->th_death);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philos[i]->eating);
		free(data->philos[i]);
	}
	free(data->philos);
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(data);
	// if (!data->loop)
		// pthread_mutex_unlock(&data->write);
	pthread_mutex_destroy(&data->write);
}

void	*post_mortem(void *data)
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
			philo->data->loop = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		if (philo->data->philos[philo->data->n_philo - 1]->nb_meals
			== philo->data->n_meal)
		{
			pthread_mutex_lock(&philo->eating);
			philo->data->loop = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		usleep(100);
	}
	return (NULL);
}

int	start_game(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = ft_get_time();
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philos[i]->th_philo, NULL,
			philo_life, data->philos[i]) != 0)
			return (-1);
		usleep(70);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philos[i]->th_death, NULL,
			post_mortem, data->philos[i]) != 0)
			return (-1);
		usleep(70);
	}
	while (data->loop)
		continue ;
	end_game(data);
	return (0);
}

int main(int ac, char **av)
{
	t_data	*game;

	game = NULL;
	if (ac != 5 && ac != 6)
		return (ft_error(ARG_ERR));
	if (ft_init(&game, ac, av) == -1)
		return (-1);
	if (start_game(game) == -1)
		return (ft_error("Game failed\n"));
	return (0);
}
