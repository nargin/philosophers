/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 23:20:23 by nrgn              #+#    #+#             */
/*   Updated: 2023/04/27 16:34:21 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_value(int value, int order)
{
	if ((value < 2 || value > 200) && order == 0)
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
	else if (value < 0 && order == 4)
		return (ft_error("Error: number of time each philosopher must eat is too short\n"));
	return (0);
}

int	ft_init_philo(int ac, char *av[], t_philo *philo)
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
	philo->nb_eat = 0;
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

int main(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (ft_error("Error: malloc failed\n"));
	if (ac != 5 && ac != 6)
		return (ft_error(ARG_ERR));
	if (ft_init_philo(ac, av, philo) == -1)
		return (ft_error(ARG_TOO_LOW));
	printf("nb_philo = %d\n", philo->nb_philo);
	printf("time_to_die = %d\n", philo->time_to_die);
	printf("time_to_eat = %d\n", philo->time_to_eat);
	printf("time_to_sleep = %d\n", philo->time_to_sleep);
	if (ac == 6)
		printf("nb_eat = %d\n", philo->nb_eat);
	philo->start_time = ft_get_time();
	printf("start_time = %ld\n", philo->start_time);
	usleep(2000);
	printf("time = %ld\n", ft_get_time() - philo->start_time);
}  