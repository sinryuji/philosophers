/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:18:43 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/11 21:43:21 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//static int	monitoring_philos(t_table *table)
//{
//	int	i;
//
//	printf("in monitoring\n");
//	while (table->finish == FALSE)
//	{
//		i = 0;
//		while (i < table->number_of_philo)
//		{
//			if (get_current_time() - table->philos[i].eat_start_time \
//				> table->time_to_die)
//			{
//				table->philos[i].status = DIED;
//				table->finish = TRUE;
//				break ;
//			}
//			i++;
//		}
//		usleep(1000);
//	}
//	return (EXIT_SUCCESS);
//}

static int	create_thread(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].status = SIT;
		if (pthread_create(&table->philos[i].thread, NULL, &routine, \
			(void *)&table->philos[i]))
			return (ERR_CREATE_THREAD);
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
//	return (monitoring_philos(table));
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
		usleep(50);
	}
	return (TRUE);
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
