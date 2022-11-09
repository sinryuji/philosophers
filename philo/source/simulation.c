/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:18:43 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/09 18:35:13 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	create_thread(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	while (i < table->number_of_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine, \
			(void *)&table->philos[i]))
			return (ERR_CREATE_THREAD);
//		pthread_join(table->philos[i].thread, (void **)&status);
//		pthread_detach(table->philos[i].thread);
//		usleep(100);
		i++;
	}
	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_join(table->philos[i].thread, (void **)&status);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	is_dead(t_table *table, t_philo *philo)
{
	if (get_current_time() - philo->eat_start_time > table->time_to_die)
		return (TRUE);
	return (FALSE);
}

int	simulation(t_table *table)
{
	int	ret;

	ret = create_thread(table);
	if (ret)
		return (ret);
	return (EXIT_SUCCESS);
}
