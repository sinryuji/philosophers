/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:18:43 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/07 20:35:04 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	create_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine, \
			(void *)&table->philos[i]) != 0)
			return (ERR_CREATE_THREAD);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	simulation(t_table *table)
{
	int	ret;

	ret = create_thread(table);
	if (ret)
		return (ret);
	return (EXIT_SUCCESS);
}
