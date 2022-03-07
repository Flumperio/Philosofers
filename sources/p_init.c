/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:23:05 by juasanto          #+#    #+#             */
/*   Updated: 2022/03/07 11:52:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_main	*init_main(t_main *main, int argc, char **argv)
{
	main = ft_calloc(sizeof (t_main), 1);
	main->argc = argc;
	main->argv = argv;
	if (main->argc < 5 || main->argc > 6)
		ft_msgerror("Numero de opciones invalidas.\
		\nSolo se admiten numeros como parametros\
		\nEjemplo: ./main n1 n2 n3 n4 n5\n", -1);
	main->n_philo = (int)ft_atoi(main->argv[1]);
	main->t_die = (int)ft_atoi(main->argv[2]);
	main->t_eat = (int)ft_atoi(main->argv[3]);
	main->t_sleep = (int)ft_atoi(main->argv[4]);
	if (main->argc == 6)
		main->n_eat = (int)ft_atoi(main->argv[5]);
	return (main);
}

t_philo	*init_philo(t_philo *philos, t_main *main)
{
	int		cnt;


	cnt = -1;
	philos = ft_calloc(sizeof (t_philo), main->n_philo);
	cnt = -1;
	while (++cnt < main->n_philo)
	{
		philos[cnt].position = cnt + 1;
		philos[cnt].cnt_eat = 0;
		philos[cnt].data_p = main;
		philos[cnt].m_f_r = &main->lock_fork[cnt];
		if(cnt == 0)
			philos[cnt].m_f_l = &main->lock_fork[main->n_philo - 1];
		else
			philos[cnt].m_f_l = &main->lock_fork[cnt - 1];
		philos[cnt].time_eat = get_time();
	}
	main->time_start = get_time();
	return(philos);
}

void	init_fork(t_main *main, t_philo *philo)
{
	int		cnt;

	cnt = -1;
	main->lock_fork = ft_calloc(sizeof (pthread_mutex_t), main->n_philo);
	cnt = -1;
	while (++cnt < main->n_philo)
		pthread_mutex_init(&main->lock_fork[cnt], NULL);
	pthread_mutex_init(&main->lock_print, NULL);
	pthread_mutex_init(&main->lock_gen, NULL);
}