/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:02:55 by mait-taj          #+#    #+#             */
/*   Updated: 2024/10/25 18:06:13 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	is_eating(t_philo *philos)
{
	sem_wait(philos->l_sem);
	ft_print(philos, TAKEN);
	sem_wait(philos->r_sem);
	ft_print(philos, TAKEN);
	ft_print(philos, EAT);
	ft_sleep(philos->data->time_t_eat);
	philos->count_meal += 1;
	sem_post(philos->l_sem);	
	sem_post(philos->r_sem);
	philos->time_last_meal = get_time();
	if (philos->count_meal == philos->data->limit_meals)
		exit(0);
		// philos->is_full = true;
}

void	routine(t_philo *philos)
{
	// while (philos->data->GO == false)
	// 	;
	if (philos->id % 2 == 0)
	{
		ft_print(philos, SLEEP);
		ft_sleep(philos->data->time_t_sleep);
	}
	// if (philos->data->end_simult == true)
	// 	write(1, "GOOD\n", 5);
	while (philos->data->end_simult == false)
	{
		// write(1, "other\n", 6);
		ft_print(philos, THINK);
		is_eating(philos);
		ft_print(philos, SLEEP);
		ft_sleep(philos->data->time_t_sleep);
	}
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
		if ((data->philos[i].cid = fork()) == 0)
		{
			// data->s[i].ready = true;
			routine(&data->philos[i]);
			exit(0);
		}	
	}
}
