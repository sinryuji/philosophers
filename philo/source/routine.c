/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:34:37 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/08 20:38:48 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	pick_fork(t_table *table, t_philo *philo)
{

}

static int	eating(t_table *table, t_philo *philo)
{
	
}

static int	thinking(t_table *table, t_philo *philo)
{
	
}

static int	sleeping(t_table *table, t_philo *philo)
{
	
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->routine_start_time = get_current_time();
	while (1)
	{
		if (eating(philo->table, philo))
			break ;
		if (sleeping(philo->table, philo))
			break ;
		if (thinking(philo->table, philo))
			break ;
	}
	return (NULL);
}
