/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:42:42 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/24 14:30:05 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_destroy(&(table->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(table->printer));
	free(table->forks);
	free(table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		ret;

	ret = usage_check(argc);
	if (!ret)
		ret = init_table(argc, argv, &table);
	if (table.noe_flag == TRUE && table.number_of_eat == 0)
		return (EXIT_SUCCESS);
	if (!ret)
		ret = simulation(&table);
	if (ret)
	{
		destroy_table(&table);
		return (put_error(ret));
	}
	destroy_table(&table);
	return (EXIT_SUCCESS);
}
