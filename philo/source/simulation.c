/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:18:43 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/21 18:55:20 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>

static int	philos_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		if (table->philos[i].eat_cnt < table->number_of_eat)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	*monitoring_philos(void *arg)
{
	int		i;
	t_table	*table;

	table = arg;
	while (table->finish == FALSE)
	{
		i = 0;
		while (++i < table->number_of_philo)
		{
			if (is_dead(table, &table->philos[i]))
			{
				print_status(&table->philos[i], DIED);
				table->philos[i].status = DIED;
				table->finish = TRUE;
				break ;
			}
			i++;
		}
		if (table->noe_flag == TRUE && philos_full(table) == TRUE)
			table->finish = TRUE;
		usleep(50);
	}
	usleep(1000);
	return (NULL);
}

static int	create_thread(t_table *table)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].status = SIT;
		table->philos[i].eat_start_time = get_current_time();
		if (pthread_create(&table->philos[i].thread, NULL, &routine, \
			(void *)&table->philos[i]))
			return (ERR_CREATE_THREAD);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitoring_philos, (void *)table))
		return (ERR_CREATE_THREAD);
	pthread_detach(monitor);
	return (EXIT_SUCCESS);
}

int	philo_usleep(t_philo *philo, int time)
{
	long long	start;

	start = get_current_time();
	usleep(time * 500);
	while (TRUE)
	{
		if (get_current_time() - start >= time)
			break ;
		if (philo->status == DIED || philo->table->finish == TRUE)
			return (FALSE);
		usleep(100);
	}
	return (TRUE);
}

int	simulation(t_table *table)
{
	int			ret;
	int			i;

	ret = create_thread(table);
	if (ret)
		return (ret);
	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
