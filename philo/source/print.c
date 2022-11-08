/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:48:37 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/08 20:57:45 by hyeongki         ###   ########.fr       */
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
	if (status == DEAD)
		return ("is dead");
	return (NULL);
}

void	status_print(t_philo *philo, int status)
{
	int	time;

	pthread_mutex_lock(&philo->table->printer);
	time = get_current_time() - philo->table->start_time;
	printf("%d %d %s\n", time, philo->number, get_status(status));
	pthread_mutex_unlock(&philo->table->printer);
}