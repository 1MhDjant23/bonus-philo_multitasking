/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:39:11 by mait-taj          #+#    #+#             */
/*   Updated: 2024/10/08 15:02:44 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

long	ft_atol(char *str)
{
	long	res;
	int		signe;

	signe = 1;
	res = 0;
	while (*str && is_space(*str) == true)
		str++;
	if (*str == '-' || *(str + 1) == '+')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	return (res * signe);
}

bool	checking_valid_input(char **av)
{
	int	ac;
	int	i;

	ac = 0;
	while (av[++ac])
	{
		i = 0;
		while (av[ac][i] && is_space(av[ac][i]) == true)
			i++;
		while (av[ac][i])
		{
			if (av[ac][i] >= '0' && av[ac][i] <= '9')
				i++;
			else
				break ;
		}
		while (av[ac][i])
		{
			if (is_space(av[ac][i]) == true)
				i++;
			else
				return (false);
		}
	}
	return (true);
}
