/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:34:37 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/22 21:27:36 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	pick_fork(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->fork[LEFT]]);
	pthread_mutex_lock(&table->forks[philo->fork[RIGHT]]);
	print_status(philo, TAKEN_FORK);
}

static int	eating(t_table *table, t_philo *philo)
{
	int	ret;

	pick_fork(table, philo);
	print_status(philo, EATING);
	philo->eat_start_time = get_current_time();
	ret = philo_usleep(philo, table->time_to_eat);
	philo->eat_cnt++;
	pthread_mutex_unlock(&table->forks[philo->fork[LEFT]]);
	pthread_mutex_unlock(&table->forks[philo->fork[RIGHT]]);
	return (ret);
}

static int	sleeping(t_table *table, t_philo *philo)
{
	if (print_status(philo, SLEEPING) == FALSE)
		return (FALSE);
	return (philo_usleep(philo, table->time_to_sleep));
}

static int	thinking(t_philo *philo)
{
	return (print_status(philo, THINKING));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->number % 2 == 0)
		usleep(10000);
	while (philo->table->finish == FALSE)
	{
		if (eating(philo->table, philo) == FALSE)
			return (NULL);
		if (sleeping(philo->table, philo) == FALSE)
			return (NULL);
		if (thinking(philo) == FALSE)
			return (NULL);
	}
	return (NULL);
}
