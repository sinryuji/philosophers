/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:18:43 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/24 18:21:46 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		while (i < table->number_of_philo)
		{
			if (is_dead(table, &table->philos[i]))
			{
				print_status(&table->philos[i], DIED);
				table->philos[i].status = DIED;
				table->finish = TRUE;
				return (NULL);
			}
			i++;
		}
		if (table->noe_flag == TRUE && philos_full(table) == TRUE)
			table->finish = TRUE;
		usleep(100);
	}
	usleep(100);
	return (NULL);
}

static int	create_thread(t_table *table, int i)
{
	while (i < table->number_of_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine, \
			(void *)&table->philos[i]))
			return (ERR_CREATE_THREAD);
		i += 2;
	}
	return (EXIT_SUCCESS);
}

int	philo_usleep(t_philo *philo, int time)
{
	long long	start;

	start = get_current_time();
	usleep(time * 800);
	while (TRUE)
	{
		if (get_current_time() - start >= time)
			break ;
		if (philo->status == DIED || philo->table->finish == TRUE)
			return (FALSE);
	}
	return (TRUE);
}

int	simulation(t_table *table)
{
	int			ret;
	pthread_t	monitor;

	ret = create_thread(table, 0);
	if (ret)
		return (ret);
	ret = create_thread(table, 1);
	if (ret)
		return (ret);
	if (pthread_create(&monitor, NULL, monitoring_philos, (void *)table))
		return (ERR_CREATE_THREAD);
	pthread_detach(monitor);
	return (EXIT_SUCCESS);
}
