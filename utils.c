/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:49:05 by nrgn              #+#    #+#             */
/*   Updated: 2023/05/04 18:45:22 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (-1);
}

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
	else if (value < 1 && order == 4)
		return (ft_error(MEALS));
	return (0);
}

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