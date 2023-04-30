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

void	*start_routine(void *data)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)data;
	while (philo->din_table->death)
	{
		eat_routine(philo);
		print_status(philo->din_table, philo->pid, "is sleeping\n");
		time = ft_time_in_ms();
		usleep(philo->din_table->time_to_sleep * 1000 - 16000);
		while (ft_time_in_ms() - time < philo->din_table->tts)
			continue ;
		print_status(philo->din_table, philo->pid, "is thinking\n");
		usleep(100);
	}
	return (NULL);
}

