/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:35:25 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/25 15:51:47 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	set_args(t_table *table, int argc, char **argv)
{
	table->number_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->noe_flag = FALSE;
	table->finish = FALSE;
	if (argc == 5)
		table->number_of_eat = 0;
	else
	{
		table->number_of_eat = ft_atoi(argv[5]);
		table->noe_flag = TRUE;
	}
}

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
	memset(table->philos, 0, sizeof(t_philo) * table->number_of_philo);
	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].number = i + 1;
		table->philos[i].eat_cnt = 0;
		table->philos[i].fork[LEFT] = i % table->number_of_philo;
		table->philos[i].fork[RIGHT] = (i + 1) % table->number_of_philo;
		table->philos[i].table = table;
		pthread_mutex_init(&table->philos[i].status_mutex, NULL);
		table->philos[i].live_time = get_current_time();
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_table(int argc, char **argv, t_table *table)
{
	int				ret;

	memset(table, 0, sizeof(t_table));
	set_args(table, argc, argv);
	ret = argment_check(table);
	if (ret)
		return (ret);
	if (pthread_mutex_init(&table->printer, NULL) == -1)
		return (ERR_INIT_MUTEX);
	if (pthread_mutex_init(&table->table_mutex, NULL) == -1)
		return (ERR_INIT_MUTEX);
	ret = init_forks(table);
	if (ret)
		return (ret);
	ret = init_philo(table);
	if (ret)
		return (ret);
	table->start_time = get_current_time();
	return (EXIT_SUCCESS);
}
