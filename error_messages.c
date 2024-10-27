/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:17:04 by mait-taj          #+#    #+#             */
/*   Updated: 2024/10/09 19:47:53 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	err_input(t_enum stat)
{
	if (stat == INP)
	{
		printf(""YELL BOLD"Usage:"RESET" ./philo num_of_philo ");
		printf("time_to_die time_to_eat");
		printf(" time_to_sleep ["UNDER BOLD"n_of_meals"RESET"]\n");
	}
	else if (stat == INV)
	{
		printf(""RED BOLD"Oops!!"RESET" "BOLD"enter only ");
		printf("positive digit"RESET"\n");
	}
	else if (stat == INIT)
	{
		printf(""BOLD RED"Oops!!"RESET" "BOLD"number you ");
		printf("entered most be integer and sup strict to 0"RESET"\n");
	}
	else if (stat == RES)
		printf(""BOLD"Oops!! Faills to Create a Semaphore."RESET"\n");
	else if (stat == DIN)
		printf(""BOLD"Oops!!"RESET" Error occur when thread's starting!\n");
	return ;
}
