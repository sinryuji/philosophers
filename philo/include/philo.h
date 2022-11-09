/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:43:19 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/08 22:08:20 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define LEFT 0
# define RIGHT 1

# define TRUE 1
# define FALSE 0

enum e_error_type
{
	ERR_USG = 1,
	ERR_PHILO_NUM,
	ERR_EAT_NUM,
	ERR_MALLOC,
	ERR_GETTIME,
	ERR_INIT_MUTEX,
	ERR_CREATE_THREAD
};

enum e_status
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD	
};

typedef struct s_philo
{
	pthread_t		thread;
	int				number;
	int				fork[2];
	int				eat_cnt;
	int				eat_start_time;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				number_of_philo;
	int				time_to_die;
	int		 		time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer;
	struct s_philo	*philos;
}	t_table;

/* init.c */
int		init_table(int argc, char **argv, t_table *table);

/* util.c */
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		get_current_time(void);

/* error.c */
void	put_error(int err);
int		usage_check(int argc);
int		argment_check(t_table *table);

/* simulation */
int		simulation(t_table *table);
int		is_dead(t_table *table, t_philo *philo);

/* routine.c */
void	*routine(void *arg);

/* print.c */
void	print_status(t_philo *philo, int status);

#endif
