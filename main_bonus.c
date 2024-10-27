/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:15:11 by mait-taj          #+#    #+#             */
/*   Updated: 2024/10/25 22:20:59 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int ac, char **av)
{
	t_program data;

	if (ac != 5 && ac != 6)
		return (err_input(INP), 1);
	if (!checking_valid_input(av))
		return (err_input(INV), 1);
	if (!init_data(av, &data))
		return (err_input(INIT), 1);
	if (data.limit_meals == 0)
	{
		printf(""UNDER BOLD"give at least one meal to philo"RESET"\n");
		return (1);
	}
	if (!init_resource(&data))
		return (err_input(RES), 1);
	if (pthread_create(&data.tid, NULL, monitoring, &data) != 0)
		return (1);
	start_dinner(&data);
	int i = -1;
	while (++i < data.n_of_p)
		waitpid(data.philos[i].cid, 0, 0);
	if (pthread_join(data.tid, NULL) != 0)
		return (write(2, "can't join thread.\n", 19));
	// write(1, "HERE\n", 5);
	i = -1;
	while (++i < data.n_of_p)
	{
		kill(data.philos[i].cid, SIGTERM);
	}
	
    return 0;
}
