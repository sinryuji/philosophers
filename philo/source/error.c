/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:33:32 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/21 18:49:48 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static char	*get_err_msg(int errno)
{
	if (errno == ERR_USG)
		return ("Invalid number of factors.\n\
Usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] \
[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
	else if (errno == ERR_PHILO_NUM)
		return ("Invalid argument philosophers number. Must be 1 ~ 200.");
	else if (errno == ERR_EAT_NUM)
		return ("Invalid argument number of times must eat. Must be positive\n");
	else if (errno == ERR_MALLOC)
		return ("Malloc failed\n");
	else if (errno == ERR_INIT_MUTEX)
		return ("Init metex failed\n");
	else if (errno == ERR_WRONG_TIME)
		return ("Invalid argument of type time\nUsage: greather than 59");
	return (NULL);
}

int	put_error(int errno)
{
	write(STDOUT_FILENO, get_err_msg(errno), ft_strlen(get_err_msg(errno)));
	return (EXIT_FAILURE);
}

int	usage_check(int argc)
{
	if (argc == 5 || argc == 6)
		return (EXIT_SUCCESS);
	return (ERR_USG);
}

int	argment_check(t_table *table)
{
	if (table->number_of_philo < 1 || table->number_of_philo > 200)
		return (ERR_PHILO_NUM);
	else if (table->number_of_eat < 0)
		return (ERR_EAT_NUM);
	else if (table->time_to_die < 60
		|| table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (ERR_WRONG_TIME);
	return (EXIT_SUCCESS);
}
