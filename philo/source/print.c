/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:48:37 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/13 17:55:08 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	died_check(t_philo *philo)
{
	if (philo->status == DIED || philo->table->finish == TRUE)
		return (FALSE);
	return (TRUE);
}

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
	uint64_t	time;

	if (died_check(philo) == FALSE)
		return (FALSE);
	pthread_mutex_lock(&philo->table->printer);
	time = get_current_time() - philo->table->start_time;
	printf("%llu %d %s\n", time, philo->number, get_status(status));
	pthread_mutex_unlock(&philo->table->printer);
	return (TRUE);
}
