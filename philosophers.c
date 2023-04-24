/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrgn <nrgn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:20:23 by nrgn              #+#    #+#             */
/*   Updated: 2023/04/24 17:28:20 by nrgn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_philo	*philo;
	int		i;

	if (ac != 5 && ac != 6)
		return (ft_error("Error: invalid number of arguments\n"));
	if (!(philo = malloc(sizeof(t_philo))))
		return (ft_error("Error: malloc failed\n"));
	philo->num = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->num_of_eat = 0;
	if (ac == 6)
		philo->num_of_eat = ft_atoi(av[5]);
	if (philo->num <= 0 || philo->time_to_die <= 0 || philo->time_to_eat <= 0
		|| philo->time_to_sleep <= 0 || philo->num_of_eat < 0)
		return (ft_error("Error: invalid argument\n"));
	if (!(philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num)))
		return (ft_error("Error: malloc failed\n"));
}