/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:18:43 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/12 17:06:04 by hyeongki         ###   ########.fr       */
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

static int	monitoring_philos(t_table *table)
{
	int	i;

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
				break ;
			}
			i++;
		}
		if (table->noe_flag == TRUE && philos_full(table) == TRUE)
		{
			table->finish = TRUE;
			break ;
		}
		usleep(100);
	}
	usleep(100);
	return (EXIT_SUCCESS);
}

static int	create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].status = SIT;
		if (pthread_create(&table->philos[i].thread, NULL, &routine, \
			(void *)&table->philos[i]))
			return (ERR_CREATE_THREAD);
		pthread_detach(table->philos[i].thread);
		usleep(50);
		i++;
	}
	return (monitoring_philos(table));
}

int	philo_usleep(t_philo *philo, int time)
{
	int	start;

	start = get_current_time();
	while (TRUE)
	{
		if (get_current_time() - start >= time)
			break ;
		if (philo->status == DIED || philo->table->finish == TRUE)
			return (FALSE);
		usleep(50);
	}
	return (TRUE);
}

int	simulation(t_table *table)
{
	int	ret;

	ret = create_thread(table);
	if (ret)
		return (ret);
	return (EXIT_SUCCESS);
}
