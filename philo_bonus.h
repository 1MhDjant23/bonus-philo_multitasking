/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:13:30 by mait-taj          #+#    #+#             */
/*   Updated: 2024/10/25 10:38:15 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS
#define PHILO_BONUS

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELL "\033[33m"
# define BLUE "\033[44m"
# define BOLD "\033[1m"
# define UNDER "\033[4m"

#include <stdbool.h>
#include <signal.h>
#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef	struct s_philo	t_philo;
typedef	struct s_forks	t_forks;

typedef enum s_enum
{
	EAT,
	THINK,
	SLEEP,
	TAKEN,
	DEAD,
	INV,
	INP,
	INIT,
	RES,
	DIN,
}
				t_enum;
/*________________ Struct of Programe ______________________*/

typedef struct s_program
{
	long		n_of_p;
	long		time_t_die;
	long		time_t_eat;
	long		time_t_sleep;
	long		limit_meals;
	long		time_of_starting;
	sem_t		*forks;
	sem_t		*print;
	bool		end_simult;
	pthread_t	tid;
	t_philo		*philos;
}				t_program;

struct s_philo
{
	int			id;
	long		count_meal;
	long		time_last_meal;
	pid_t		cid;
	bool		is_full;
	t_program	*data;
};



void	ft_sleep(long x);
void	err_input(t_enum stat);
void	start_dinner(t_program *data);
bool	checking_valid_input(char **av);
bool	init_data(char **av, t_program *data);
long	ft_atol(char *str);
void	init_resource(t_program *data);
long	get_time(void);
void	ft_print(t_philo *philos, t_enum status);
void	*monitoring(void *arg);
void	*safe_malloc(size_t size);


#endif