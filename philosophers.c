/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:20:23 by nrgn              #+#    #+#             */
/*   Updated: 2023/05/04 19:26:18 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int main(int ac, char **av)
{
	t_data	*game;

	game = NULL;
	if (ac != 5 && ac != 6)
		return (ft_error(ARG_ERR));
	if (ft_init(&game, ac, av) == -1)
		return (-1);
	start_game(game);
	return (0);
}
