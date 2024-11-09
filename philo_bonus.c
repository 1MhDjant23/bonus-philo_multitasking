/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:34:48 by mait-taj          #+#    #+#             */
/*   Updated: 2024/11/08 22:19:07 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	init_data(char **av, t_program *data)
{
	data->n_of_p = ft_atol(av[1]);
	data->time_t_die = ft_atol(av[2]);
	data->time_t_eat = ft_atol(av[3]);
	data->time_t_sleep = ft_atol(av[4]);
	if (!av[5])
		data->limit_meals = -1;
	else
		data->limit_meals = ft_atol(av[5]);
	if (data->n_of_p > INT_MAX || data->n_of_p <= 0)
		return (false);
	else if (data->time_t_die > INT_MAX)
		return (false);
	if (data->time_t_eat > INT_MAX)
		return (false);
	if (data->time_t_sleep > INT_MAX)
		return (false);
	return (true);
}

void	unlink_semaphore(void)
{
	sem_unlink("forks");
	sem_unlink("print");
}

void	init_semaphore(t_program *data)
{
	unlink_semaphore();
	data->forks = sem_open("forks", O_EXCL | O_CREAT, 0600, data->n_of_p);
	data->print = sem_open("print", O_EXCL | O_CREAT, 0600, 1);
}

void	init_philos(t_program *data)
{
	int	n_of_p;
	int	i;

	i = -1;
	n_of_p = data->n_of_p;
	while (++i < n_of_p)
	{
		data->philos[i].id = i + 1;
		data->philos[i].count_meal = 0;
		data->philos[i].is_full = false;
		data->philos[i].time_last_meal = get_time();
	}
	data->end_simult = false;
	data->time_of_starting = get_time();
}

void	init_resource(t_program *data)
{
    int i;

	i = -1;
    data->philos = safe_malloc(sizeof(t_philo) * data->n_of_p);
	while (++i < data->n_of_p)
		data->philos[i].data = data;
	init_semaphore(data);
	init_philos(data);
}


// fork\\\\\\\\\\\\\\\\\\\\\\\
// fork\\\\\\\\\\\\\\\\\\\\\\
// fork\\\\\\\\\\\\\\\\\\\\\\
// fork/////////////////////
