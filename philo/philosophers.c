/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:20:23 by nrgn              #+#    #+#             */
/*   Updated: 2023/05/07 14:24:11 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_game(t_data *data)
{
	int	i;

	// i = -1;
	// if (data->n_philo == 1)
	// 	pthread_detach(data->philos[0]->th_philo);
	// else
	// {
	// 	while (++i < data->n_philo)
	// 	{
	// 		pthread_join(data->philos[i]->th_philo, NULL);
	// 		pthread_join(data->philos[i]->th_death, NULL);
	// 	}
	// }
	i = -1;
	while (++i < data->n_philo)
	{
		// pthread_mutex_destroy(&data->philos[i]->eating);
		free(data->philos[i]);
	}
	free(data->philos);
	i = -1;
	// while (++i < data->n_philo)
	// 	pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	// pthread_mutex_destroy(&data->write);
	free(data);
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
		else if (philo->data->philos[philo->data->n_philo - 1]->nb_meals
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
		data->philos[i]->last_eat = ft_get_time();
		if (pthread_create(&data->philos[i]->th_philo, NULL,
			&philo_life, data->philos[i]) != 0)
			return (1);
		usleep(100);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philos[i]->th_death, NULL,
			&post_mortem, data->philos[i]) != 0)
			return (1);
		usleep(100);
	}
	while (data->loop)
		continue ;
	return (0);
}

int main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (ft_error(ARG_ERR));
	if (check_arg(av) == 1)
	{
		data = NULL;
		data = ft_init(av);
		if (!data)
			return (ft_error(MALLOC_ERR));
		if (start_game(data))
			return (ft_error(THREAD_ERR));
	}
	return (0);
}
