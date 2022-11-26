/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:34:37 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/27 05:25:26 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	eating(t_table *table, t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&table->forks[philo->fork[LEFT]]);
	if (philo->fork[LEFT] == philo->fork[RIGHT])
	{
		// TODO: 구현 꼭 하기 >_= (으아아~ 기모찌 와루이~~)
	}
	pthread_mutex_lock(&table->forks[philo->fork[RIGHT]]);
	if (print_status(philo, TAKEN_FORK) == FALSE)
		return (FALSE);
	pthread_mutex_lock(&philo->status_mutex);
	philo->eat_cnt++;
	philo->live_time = get_current_time();
	pthread_mutex_unlock(&philo->status_mutex);
	print_status(philo, EATING);
	ret = philo_usleep(philo, table->time_to_eat);
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
	usleep(100);
	return (print_status(philo, THINKING));
}

static int finish_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_mutex);
	if (philo->table->finish == TRUE)
	{
		pthread_mutex_unlock(&philo->table->table_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->table->table_mutex);
	return (FALSE);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		if (finish_check(philo) == TRUE)
			return (NULL);
		if (eating(philo->table, philo) == FALSE)
			return (NULL);
		if (sleeping(philo->table, philo) == FALSE)
			return (NULL);
		if (thinking(philo) == FALSE)
			return (NULL);
	}
	return (NULL);
}
