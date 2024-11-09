/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:02:55 by mait-taj          #+#    #+#             */
/*   Updated: 2024/11/08 22:19:16 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	is_eating(t_philo *philos)
{
	sem_wait(philos->data->forks);
	ft_print(philos, TAKEN);
	sem_wait(philos->data->forks);
	ft_print(philos, TAKEN);
	ft_print(philos, EAT);
	ft_sleep(philos->data->time_t_eat);
	philos->count_meal += 1;
	philos->time_last_meal = get_time();
	sem_post(philos->data->forks);	
	sem_post(philos->data->forks);
	if (philos->count_meal == philos->data->limit_meals)
	{
		philos->is_full = true;
		exit(EXIT_SUCCESS);
	}
}

void	routine(t_philo *philos)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, monitor, philos->data);
	if (philos->id % 2 == 0)
	{
		ft_print(philos, SLEEP);
		ft_sleep(philos->data->time_t_sleep);
	}
	while (philos->data->end_simult == false)
	{
		ft_print(philos, THINK);
		is_eating(philos);
		ft_print(philos, SLEEP);
		ft_sleep(philos->data->time_t_sleep);
	}
	pthread_join(tid, NULL);
	exit(EXIT_SUCCESS);
}


void	start_dinner(t_program *data)
{
	int	n_o_p;
	int	i;

	n_o_p = data->n_of_p;
	i = -1;
	data->time_of_starting = get_time();
	while (++i < n_o_p)
	{
		data->philos[i].cid = fork();
		if (data->philos[i].cid < 0)
			exit(EXIT_FAILURE);
		if (data->philos[i].cid == 0)
		{
			routine(&data->philos[i]);
			exit(EXIT_SUCCESS);
		}
	}
	i = -1;
	while (++i < n_o_p)
	{
		waitpid(data->philos[i].cid, 0, 0);
	}
	
}
