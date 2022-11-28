/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:48:37 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/28 15:06:08 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static char	*get_status(int status)
{
	if (status == TAKEN_FORK)
		return ("has taken a fork");
	if (status == EATING)
		return ("is eating");
	if (status == SLEEPING)
		return ("is sleeping");
	if (status == THINKING)
		return ("is thinking");
	if (status == DIED)
		return ("died");
	return (NULL);
}

int	print_status(t_philo *philo, int status)
{
	long long	time;

	if (status == DIED)
	{
		set_true(philo->table);
		pthread_mutex_lock(&philo->table->printer);
		time = get_current_time() - philo->table->start_time;
		printf("%llu %d %s\n", time, philo->number, get_status(status));
		pthread_mutex_unlock(&philo->table->printer);
		return (FALSE);
	}
	pthread_mutex_lock(&philo->table->table_mutex);
	if (philo->table->finish == TRUE)
	{
		pthread_mutex_unlock(&philo->table->table_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->table->table_mutex);
	pthread_mutex_lock(&philo->table->printer);
	time = get_current_time() - philo->table->start_time;
	printf("%llu %d %s\n", time, philo->number, get_status(status));
	pthread_mutex_unlock(&philo->table->printer);
	return (TRUE);
}
