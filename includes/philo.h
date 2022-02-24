/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:29 by juasanto          #+#    #+#             */
/*   Updated: 2022/02/21 13:29:22 by                  ###   ########.fr       */
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

//typedef struct s_main t_main;
/*
** Main Structures
*/

typedef struct			s_main
{
int					argc;
char				**argv;
int					tmp;
int					n_philo;
int					t_die;
int					t_eat;
int					t_sleep;
int					n_eat;
pthread_mutex_t		*lock_fork;
pthread_mutex_t		lock_print;
pthread_mutex_t		lock_gen;
struct s_philo		*philos;
}						t_main;

/*
** Philo Structures
*/
typedef struct			s_philo
{
pthread_t			thread;
pthread_mutex_t		m_f_r;
pthread_mutex_t		m_f_l;

int					position;
int					cnt_eat;
int					fork;
int					f_r;
int					f_l;
unsigned long		time_start;
unsigned long		time_dead;
unsigned long		time_eat;
struct timeval		time;
t_main				data_p;
}						t_philo;

/*
** Funtions;
*/
t_main			*init_main(t_main *philo, int argc, char **argv);
t_philo			*init_philo(t_philo *philos, t_main *main);
pthread_mutex_t	*init_fork(pthread_mutex_t *fork, t_main *main, t_philo *philo);
int				chk_args(t_main *philo);
unsigned long	get_time(void);

/*
** Aux Funtions
*/
void			*ft_calloc(size_t num, size_t size);
long long int	ft_atoi(const char *str);
void			ft_msgerror(char *str, int errno);
#endif
