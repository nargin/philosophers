/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrgn <nrgn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:20:23 by nrgn              #+#    #+#             */
/*   Updated: 2023/05/04 12:38:48 by nrgn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_value(int value, int order)
{	if ((value < 2 || value > 200) && order == 0)
	{
		if (value < 2)
			return (ft_error("Error: not enough philosophers\n"));
		else
			return (ft_error("Error: too many philosophers\n"));
	}
	else if (value < 60 && order == 1)
		return (ft_error("Error: time to die is too short\n"));
	else if (value < 60 && order == 2)
		return (ft_error("Error: time to eat is too short\n"));
	else if (value < 60 && order == 3)
		return (ft_error("Error: time to sleep is too short\n"));
	else if (value < -1 && order == 4)
		return (ft_error("Error: number of time each philosopher must eat is too short\n"));
	return (0);
}

int	ft_init_arg(int ac, char *av[], t_philo *philo)
{
	philo->nb_philo = ft_atoi(av[1]);
	if (check_value(philo->nb_philo, 0) == -1)
		return (-1);
	philo->time_to_die = ft_atoi(av[2]);
	if (check_value(philo->time_to_die, 1) == -1)
		return (-1);
	philo->time_to_eat = ft_atoi(av[3]);
	if (check_value(philo->time_to_eat, 2) == -1)
		return (-1);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (check_value(philo->time_to_sleep, 3) == -1)
		return (-1);
	philo->nb_eat = -1;
	if (ac == 6)
	{
		philo->nb_eat = ft_atoi(av[5]);
		if (check_value(philo->nb_eat, 4) == -1)
			return (-1);
	}
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!philo->forks)
		return (-1);
	return (0);
}

pthread_mutex_t	*ft_init_forks(int nb_philo)
{
	pthread_mutex_t	*fork;
	int				i;

	i = -1;
	fork = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!fork)
		return (NULL);
	while (++i < nb_philo)
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (NULL);
	return (fork);
}

t_philo	**ft_init_time(t_skateboard *pasta)
{
	t_philo	**philo_tab;
	int		i;

	i = -1;
	philo_tab = malloc(sizeof(t_philo *) * pasta->nb_philo + 1);
	if (!philo_tab)
		return (NULL);
	while (++i < pasta->nb_philo)
	{
		philo_tab[i] = malloc(sizeof(t_philo));
		if (!philo_tab[i])
			return (NULL);
		if (pthread_mutex_init(&philo_tab[i]->eating, NULL) != 0)
			return (NULL);
		philo_tab[i]->skateboard = pasta;
		philo_tab[i]->id = i;
		philo_tab[i]->is_eating = 0;
		philo_tab[i]->nb_eat = 0;
		philo_tab[i]->left = i;
		philo_tab[i]->right = (i + 1) % pasta->nb_philo;
	}
	philo_tab[i] = NULL;
	return (philo_tab);
}

int	ft_init_thread(t_skateboard *pasta)
{
	int			i;

	i = -1;
	pasta->start_time = ft_get_time();
	while (++i < pasta->nb_philo)
	{
		if (pthread_create(&pasta->philos[i]->thd, NULL,
			philo_life, pasta->philos[i]) != 0)
			return (-1);
	}
	i = -1;
	while (++i < pasta->nb_philo)
	{
		if (pthread_create(&pasta->philos[i]->thp, NULL,
			post_mortem, pasta->philos[i]) != 0)
			return (-1);
	}
	while (!pasta->is_dead)
		continue ;
	return (0);
	
}

int	ft_init(t_data **game, int ac, char *av[])
{
	*game = malloc(sizeof(t_data));
	if (!*game)
		return (ft_error(MALLOC_ERR));
	ft_init_arg(ac, av, *game)
	(*game)->pasta->forks = ft_init_forks((*game)->pasta->nb_philo);
	if (!(*game)->pasta->forks)
		return (ft_error(MALLOC_ERR));
	(*game)->pasta->philos = ft_init_philo((*game)->pasta);
	if (!(*game)->pasta->philos)
		return (ft_error(MALLOC_ERR));
	if (ft_init_thread((*game)->pasta) == -1)
		return (ft_error(THREAD_ERR));
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
	start_game(game);
	//ft_init_arg(ac, av, game
	//ft_init_struct(game->n_philo);
	//ft_init_philo(game);
	//ft_init_thread(game) == -1)
	return (0);
}
