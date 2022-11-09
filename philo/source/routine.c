/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:34:37 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/09 19:09:03 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	pick_fork(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->fork[LEFT]]);
	pthread_mutex_lock(&table->forks[philo->fork[RIGHT]]);
	print_status(philo, TAKEN_FORK);
}

static void	eating(t_table *table, t_philo *philo)
{
	pick_fork(table, philo);
	print_status(philo, EATING);
	philo->eat_start_time = get_current_time();
	usleep(table->time_to_eat * 1000);
	philo->eat_cnt++;
	pthread_mutex_unlock(&table->forks[philo->fork[LEFT]]);
	pthread_mutex_unlock(&table->forks[philo->fork[RIGHT]]);
}

static void	sleeping(t_table *table, t_philo *philo)
{
	print_status(philo, SLEEPING);
	usleep(table->time_to_sleep * 1000);
}

static void	thinking(t_table *table, t_philo *philo)
{
	(void)table;
	print_status(philo, THINKING);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		eating(philo->table, philo);
		sleeping(philo->table, philo);
		thinking(philo->table, philo);
	}
	print_status(philo, DEAD);
	return (NULL);
}
