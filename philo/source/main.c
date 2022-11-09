/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:42:42 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/09 17:30:16 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		ret;

	ret = usage_check(argc);
	if (!ret)
		ret = init_table(argc, argv, &table);
	if (!ret)
		ret = simulation(&table);
	if (ret)
	{
		put_error(ret);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
