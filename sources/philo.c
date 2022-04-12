/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:09 by juasanto          #+#    #+#             */
/*   Updated: 2022/04/12 14:19:09 by juasanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	one_philo(t_philo *philo)
{
	printf("0ms Philo[1] [32mhas taken a fork.[0m\n");
	fn_usleep_1(philo->data_p->t_die);
	printf("%ims Philo[1] [35mis died.[0m\n", philo->data_p->t_die);
	philo->data_p->is_liv = 1;
	philo->data_p->n_philo = -1;
}

void	*philo_routine(void *n_philo)
{
	t_philo			*philo;

	philo = (t_philo *)n_philo;
	if (philo->position % 2 == 0)
		fn_usleep_1(2);
	while (philo->cnt_eat != philo->data_p->n_eat && fn_chk_live(philo) == 0)
	{
		pick_fork(philo);
		philo_eat(philo);
		if (fn_chk_live(philo) == 0)
			philo_sleep(philo);
		if (fn_chk_live(philo) == 0)
			philo_think(philo);
	}
	return (NULL);
}

void	philo_dead(t_main *main, t_philo *philos, int c1)
{
	fn_print(&philos[c1], "is died.\033[0m");
	pthread_mutex_lock(&philos->data_p->lock_think);
	main->is_liv = 1;
	pthread_mutex_unlock(&philos->data_p->lock_think);
	main->is_eat = 1;
}

void	chk_is_live(t_main *main, t_philo *philos)
{
	int				c2;

	while (main->is_eat == 0 && main->is_liv == 0)
	{
		main->c1 = -1;
		while (++main->c1 < main->n_philo && main->is_liv == 0)
		{
			c2 = -1;
			pthread_mutex_lock(&main->lock_eat);
			while (++c2 < main->n_philo && \
							philos[c2].cnt_eat == main->n_eat)
			main->is_eat = (c2 == main->n_philo);
			if (c2 == main->n_philo)
			{
				pthread_mutex_lock(&philos->data_p->lock_think);
				main->is_liv = 1;
				pthread_mutex_unlock(&philos->data_p->lock_think);
				main->is_eat = 1;
			}
			else if ((int)(get_time() - philos[main->c1].time_eat) > \
						main->t_die && main->is_liv == 0)
				philo_dead(main, philos, main->c1);
			pthread_mutex_unlock(&main->lock_eat);
		}
	}
}

int	main(int argc, char **argv)
{
	t_main			*main;
	t_philo			*philos;
	int				cnt;

	cnt = -1;
	main = NULL;
	philos = NULL;
	main = init_main(main, argc, argv);
	chk_args(main);
	init_fork(main);
	philos = init_philo(philos, main);
	if (philos->data_p->n_philo == 1)
		one_philo(philos);
	while (++cnt < main->n_philo)
		pthread_create(&philos[cnt].thread, NULL, &philo_routine, &philos[cnt]);
	chk_is_live(main, philos);
	cnt = -1;
	while (++cnt < main->n_philo)
		pthread_join(philos[cnt].thread, NULL);
	fn_clean(main, philos);
	return (0);
}
