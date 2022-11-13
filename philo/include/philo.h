/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:43:19 by hyeongki          #+#    #+#             */
/*   Updated: 2022/11/13 18:17:25 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	ERR_INIT_MUTEX,
	ERR_CREATE_THREAD
};

enum e_status
{
	SIT,
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_philo
{
	pthread_t		thread;
	int				number;
	int				fork[2];
	int				eat_cnt;
	uint64_t		eat_start_time;
	int				status;
	struct s_table	*table;
	pthread_mutex_t	status_mutex;
}	t_philo;

typedef struct s_table
{
	int				number_of_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		start_time;
	int				number_of_eat;
	int				noe_flag;
	int				finish;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer;
	struct s_philo	*philos;
}	t_table;

/* init.c */
int		init_table(int argc, char **argv, t_table *table);

/* util.c */
int			ft_strlen(char *str);
int			ft_atoi(char *str);
uint64_t	get_current_time(void);
int			is_dead(t_table *table, t_philo *philo);

/* error.c */
int		put_error(int err);
int		usage_check(int argc);
int		argment_check(t_table *table);

/* simulation */
int		simulation(t_table *table);
int		philo_usleep(t_philo *philo, uint64_t time);

/* routine.c */
void	*routine(void *arg);

/* print.c */
int		print_status(t_philo *philo, int status);

#endif
