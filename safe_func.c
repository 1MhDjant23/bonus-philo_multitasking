/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:39:54 by mait-taj          #+#    #+#             */
/*   Updated: 2024/10/09 19:44:53 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	safe_malloc(t_program *data)
{
    if (!data->forks && !data->philos)
	{
		printf("malloc faill to alloc mutex and thread\n");
		return (false);
	}
	if (!data->forks && data->philos)
	{
		printf("malloc faill to alloc mutex\n");
		free(data->philos);
		return (false);
	}
	if (!data->philos && data->forks)
	{
		printf("malloc faill to alloc thread\n");
		free(data->forks);
		return (false);
	}
	return (true);
}