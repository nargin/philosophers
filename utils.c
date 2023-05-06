/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:49:05 by nrgn              #+#    #+#             */
/*   Updated: 2023/05/06 15:24:25 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long	ft_get_time(void)
{
	struct timeval	tv;
	unsigned long long		time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000));
	return (time);
}

int	ft_error(char *str)
{
	int i;

	i = 0;
	while (str[i] && str)
		write(2, &str[i++], 1);
	return (-1);
}

int		check_value(int value, int order)
{	if ((value < 1 || value > 200) && order == 0)
	{
		if (value < 1)
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
	else if (value < 1 && order == 4)
		return (ft_error(MEALS));
	return (0);
}

// void	print_struct(t_data *game)
// {
// 	int	i;

// 	i = -1;
// 	printf("start_time = %lld\n", game->start_time);
// 	printf("loop = %d\n", game->loop);
// 	printf("n_philo = %d\n", game->n_philo);
// 	printf("time_to_die = %d\n", game->tdie);
// 	printf("time_to_eat = %d\n", game->teat);
// 	printf("time_to_sleep = %d\n", game->tsleep);
// 	printf("n_meal = %d\n", game->n_meal);
// 	while (++i < game->n_philo)
// 	{
// 		printf("\n------------------\n");
// 		printf("philos[%d]->id = %d\n", i, game->philos[i]->id);
// 		printf("philos[%d]->fork_left = %d\n", i, game->philos[i]->fork_left);
// 		printf("philos[%d]->fork_right = %d\n", i, game->philos[i]->fork_right);
// 		printf("philos[%d]->nb_meals = %d\n", i, game->philos[i]->nb_meals);
// 		printf("philos[%d]->is_eating = %d\n", i, game->philos[i]->is_eating);
// 		printf("philos[%d]->last_eat = %lld\n", i, game->philos[i]->last_eat);
// 		printf("\n------------------\n");
// 	}
// }

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	if (str[i] != '\0' || res > MAX || res < MIN)
	{
		if (res > MAX || res < MIN)
			return (ft_error("Error: invalid argument\n"));
		return (ft_error("Error: arguments contains non digit caracteres\n"));
	}
	return ((int)res * sign);
}