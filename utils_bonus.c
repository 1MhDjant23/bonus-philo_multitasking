/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:07:00 by mait-taj          #+#    #+#             */
/*   Updated: 2024/11/08 22:30:49 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct	timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));	
}

void	ft_sleep(long x)
{
	long	start;

	start = get_time();
	while ((get_time() - start) <= x);
		// usleep(500);
}

bool	base_case(t_program *data, t_enum stat)
{
	if (data->end_simult == true && stat != DEAD)
	{
		sem_post(data->print);
		return (true);
	}
	return (false);
}

void	ft_print(t_philo *philos, t_enum status)
{
	long	start;

	sem_wait(philos->data->print);
	if (base_case(philos->data, status))
		return ;
	start = philos->data->time_of_starting; 
	if (status == EAT)
		printf("%ld %d is eating\n", get_time()
			- start, philos->id);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", get_time()
			- start, philos->id);
	else if (status == THINK)
		printf("%ld %d is thinking\n", get_time()
			- start, philos->id);
	else if (status == DEAD)
		printf("%ld %d "RED BOLD"is died"RESET"\n", get_time()
			- start, philos->id);
	else if (status == TAKEN)
		printf("%ld %d has taken a fork\n", get_time()
			- start, philos->id);
	sem_post(philos->data->print);
}


bool	philo_full(t_program *data)
{
	int	n_of_p;
	int	i;

	n_of_p = data->n_of_p;
	if (data->limit_meals != -1)
	{
		i = -1;
		while (data->philos[i].is_full == true)
			i++;
		if (i == data->n_of_p)
		{
			data->end_simult = true;
			return (true);
		}
	}
	return (false);
}
bool	death(t_program *data)
{
	int	n_of_p;
	int	i;

	n_of_p = data->n_of_p;
	i = -1;
	while (++i < n_of_p)
	{
		if (get_time() - data->philos[i].time_last_meal >= data->time_t_die)
			return (true);
	}
	return (false);
}

void	*monitor(void *arg)
{
	t_program	*data;
	int			i;

	i = 0;
	data = (t_program*)arg;
	while (data->end_simult == false)
	{
		if (philo_full(data) == true)
			break ;
		if (death(data) == true)
		{
			data->end_simult = true;
			ft_print(&data->philos[i], DEAD);
			break ;
		}
	}
	i = -1;
	while (++i < data->n_of_p)
		kill(data->philos[i].cid, SIGTERM);
	// exit(EXIT_SUCCESS);
	return (NULL);
}
