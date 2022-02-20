/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:29 by juasanto          #+#    #+#             */
/*   Updated: 2022/02/03 12:31:15 by                  ###   ########.fr       */
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
** Philo Structures
*/
typedef struct			s_philo
{
	pthread_t			thread;
	pthread_mutex_t		m_f_r;
	pthread_mutex_t		m_f_l;
	pthread_mutex_t		m_fork;
	pthread_mutex_t		m_time_start;
	int					position;
	int					cnt_eat;
	int					fork;
	int					f_r;
	int					f_l;
	size_t				time_start;
	size_t				time_dead;
	size_t				time_eat;
	struct	timeval		time;
}						t_philo;

/*
** Main Structures
*/

typedef struct s_main
{
int					argc;
char				**argv;
int					tmp;
int					n_philo;
int					t_die;
int					t_eat;
int					t_sleep;
int					n_eat;
t_philo				*philos;
}						t_main;

/*
** Funtions;
*/
t_main			*init_main(t_main *philo, int argc, char **argv);
int				chk_args(t_main *philo);

/*
** Aux Funtions
*/
void			*ft_calloc(size_t num, size_t size);
long long int	ft_atoi(const char *str);
void			ft_msgerror(char *str, int errno);
#endif
