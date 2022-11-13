/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:46:02 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/13 18:16:59 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int				m_flag;
	unsigned long	result;

	m_flag = 0;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			m_flag = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > LONG_MAX && !m_flag)
		return (-1);
	if (result > LONG_MAX && m_flag)
		return (0);
	if (m_flag)
		result *= -1;
	return (result);
}

uint64_t	get_current_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

int	is_dead(t_table *table, t_philo *philo)
{
	if (get_current_time() - philo->eat_start_time > table->time_to_die)
		return (TRUE);
	return (FALSE);
}
