/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:18:43 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/15 21:32:31 by hyeongki         ###   ########.fr       */
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
				printf("time : %llu\n", get_current_time() - table->philos[i].eat_start_time);
				print_status(&table->philos[i], DIED);
				table->philos[i].status = DIED;
				table->finish = TRUE;
				break ;
			}
			i++;
			usleep(50);
		}
		if (table->noe_flag == TRUE && philos_full(table) == TRUE)
		{
			table->finish = TRUE;
			break ;
		}
		usleep(50);
	}
	usleep(2000);
	return (EXIT_SUCCESS);
}

static int	create_thread(t_table *table, int odd)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		if (i % 2 == odd)
		{
			i++;
			continue ;
		}
		table->philos[i].status = SIT;
		table->philos[i].eat_start_time = get_current_time();
		if (pthread_create(&table->philos[i].thread, NULL, &routine, \
			(void *)&table->philos[i]))
			return (ERR_CREATE_THREAD);
		pthread_detach(table->philos[i].thread);
		usleep(50);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	philo_usleep(t_philo *philo, uint64_t time)
{
	uint64_t	start;

	start = get_current_time();
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
	int	ret;

	ret = create_thread(table, 1);
	if (ret)
		return (ret);
	usleep(100);
	ret = create_thread(table, 0);
	if (ret)
		return (ret);
	return (monitoring_philos(table));
}
