/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:34:48 by mait-taj          #+#    #+#             */
/*   Updated: 2024/10/25 22:48:20 by mait-taj         ###   ########.fr       */
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

bool	Create_Semaphore(t_forks *forks, t_program *data)
{
	// int	i;

	// i = -1;
	// data->time_of_starting = 0;
	// while (++i < data->n_of_p)
	// {
		forks->sem = sem_open("Semaphore", O_CREAT | O_EXCL, 0777, data->n_of_p);
		if (forks->sem == SEM_FAILED)
		{
			// perror("sem_open");
			return (false);
		}
	// }
	return (true);
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
		// data->philos[i].l_sem = data->forks[i].sem;
		// data->philos[i].r_sem = data->forks[i + 1].sem;
		data->philos[i].is_full = false;
		data->philos[i].time_last_meal = get_time();
		data->philos[i].ready = false;
	}
	data->philos[i].r_sem = data->forks[i - 1].sem;
	data->end_simult = false;
	data->time_of_starting = get_time();
	data->GO = false;
}

bool	init_resource(t_program *data)
{
    int i;

	i = -1;
    data->forks = (t_forks*)malloc(sizeof(t_forks) * data->n_of_p);
    data->philos = (t_philo*)malloc(sizeof(t_philo) * data->n_of_p);
    if (!safe_malloc(data))
        return (false);
	while (++i < data->n_of_p)
		data->philos[i].data = data;
	if (!Create_Semaphore(data->forks, data))
	{
		free(data->forks);
		return (free(data->philos), false);
	}
	init_philos(data);
	return (true);
}
