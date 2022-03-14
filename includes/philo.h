/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:10:11 by juasanto          #+#    #+#             */
/*   Updated: 2022/03/14 14:04:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
 ** Libraries
*/
# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<time.h>
# include	<sys/time.h>
# include	<pthread.h>

/*
** Main Structure
*/

typedef struct s_main
{
	int					argc;
	char				**argv;
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	int					is_alive;
	pthread_mutex_t		*lock_fork;
	pthread_mutex_t		lock_print;
	pthread_mutex_t		lock_gen;
	unsigned long		time_start;
	struct s_philo		*philos;
}						t_main;

/*
** Philo Structures
*/
typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		*m_f_r;
	pthread_mutex_t		*m_f_l;
	int					position;
	int					cnt_eat;
	unsigned long		time_eat;
	t_main				*data_p;
}						t_philo;

/*
** Funtions;
*/
t_main			*init_main(t_main *philo, int argc, char **argv);
t_philo			*init_philo(t_philo *philos, t_main *main);
void			init_fork(t_main *main);
int				chk_args(t_main *philo);
unsigned long	get_time(void);
void			fn_usleep_1(size_t time_in_ms);

/*
** Philo Status;
*/
void			pick_fork(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *n_philo);
void			philo_think(t_philo *n_philo);

/*
** Aux Funtions
*/
void			*ft_calloc(size_t num, size_t size);
long long int	ft_atoi(const char *str);
void			ft_msgerror(char *str, int errno);
void			fn_clean(t_main *main, t_philo *philo);
void			fn_print(t_philo *philo, char *task);
#endif
