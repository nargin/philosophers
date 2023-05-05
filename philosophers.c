/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrgn <nrgn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:20:23 by nrgn              #+#    #+#             */
/*   Updated: 2023/05/05 14:50:37 by nrgn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_game(t_data **data)
{
	int	i;

	i = -1;
	(*data)->start_time = ft_get_time();
	while (++i < (*data)->n_philo)
	{
		if (pthread_create(&(*data)->philos[i]->th_philo, NULL,
			philo_life, (*data)->philos[i]) != 0)
			return ;
	}
	i = -1;
	while (++i < (*data)->n_philo)
	{
		if (pthread_create(&(*data)->philos[i]->th_death, NULL,
			post_mortem, (*data)->philos[i]) != 0)
			return ;
	}
	while (!(*data)->loop)
		continue ;
}

int main(int ac, char **av)
{
	t_data	*game;

	game = NULL;
	if (ac != 5 && ac != 6)
		return (ft_error(ARG_ERR));
	if (ft_init(&game, ac, av) == -1)
		return (-1);
	start_game(&game);
	return (0);
}
