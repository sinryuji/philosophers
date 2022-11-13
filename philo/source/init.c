/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:35:25 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/13 17:25:55 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_t) * \
	table->number_of_philo);
	if (table->forks == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < table->number_of_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) == -1)
			return (ERR_INIT_MUTEX);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_philo(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->number_of_philo);
	if (table->philos == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].number = i + 1;
		table->philos[i].eat_cnt = 0;
		table->philos[i].fork[LEFT] = i % table->number_of_philo;
		table->philos[i].fork[RIGHT] = (i + 1) % table->number_of_philo;
		table->philos[i].table = table;
		pthread_mutex_init(&table->philos[i].status_mutex, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_table(int argc, char **argv, t_table *table)
{
	int				ret;

	table->number_of_philo = ft_atoi(argv[1]);
	table->time_to_die = (uint64_t)ft_atoi(argv[2]);
	table->time_to_eat = (uint64_t)ft_atoi(argv[3]);
	table->time_to_sleep = (uint64_t)ft_atoi(argv[4]);
	table->noe_flag = FALSE;
	if (argc == 5)
		table->number_of_eat = 0;
	else
	{
		table->number_of_eat = ft_atoi(argv[5]);
		table->noe_flag = TRUE;
	}
	ret = argment_check(table);
	if (ret)
		return (ret);
	if (pthread_mutex_init(&table->printer, NULL) == -1)
		return (ERR_INIT_MUTEX);
	ret = init_forks(table);
	if (ret)
		return (ret);
	table->start_time = get_current_time();
	return (init_philo(table));
}
