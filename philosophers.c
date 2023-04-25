/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:20:23 by nrgn              #+#    #+#             */
/*   Updated: 2023/04/25 16:09:18 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (ft_error(ARG_ERROR));
	if (!(philo = malloc(sizeof(t_philo))))
		return (ft_error("Error: malloc failed\n"));
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->nb_eat = 0;
	if (ac == 6)
		philo->nb_eat = ft_atoi(av[5]);
	if ((philo->nb_philo < 2 && philo->nb_philo > 200)
		|| philo->time_to_die < 60 
		|| philo->time_to_eat < 60
		|| philo->time_to_sleep < 60
		|| philo->nb_eat < 0)
		return (ft_error("Error: invalid argument\n"));
	printf("nb_philo = %d\n", philo->nb_philo);
	printf("time_to_die = %d\n", philo->time_to_die);
	printf("time_to_eat = %d\n", philo->time_to_eat);
	printf("time_to_sleep = %d\n", philo->time_to_sleep);
	if (ac == 6)
		printf("nb_eat = %d\n", philo->nb_eat);
	philo->start_time = ft_get_time();
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	
	
}