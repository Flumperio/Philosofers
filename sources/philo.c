/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:09 by juasanto          #+#    #+#             */
/*   Updated: 2022/04/10 11:24:14 by juasanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	one_philo(t_philo *philo)
{
	printf("0ms Philo[1] [32mhas taken right fork.[0m\n");
	fn_usleep_1(philo->data_p->t_die);
	printf("%ims Philo[1] [35mis Dead.[0m\n", philo->data_p->t_die);
	philo->data_p->is_liv = 1;
	philo->data_p->n_philo = -1;
}

void	*philo_routine(void *n_philo)
{
	t_philo			*philo;
	int				chk_de;

	philo = (t_philo *)n_philo;
	if (philo->position % 2 == 0)
		fn_usleep_1(2);
	while (philo->cnt_eat != philo->data_p->n_eat && philo->data_p->is_liv == 0)
	{
		pick_fork(philo);
		pthread_mutex_lock(&philo->data_p->lock_sleep);
		chk_de = chk_dead(philo);
		pthread_mutex_unlock(&philo->data_p->lock_sleep);
		if (chk_de == 1 || philo->data_p->is_liv == 1)
			pthread_join(philo->thread, NULL);
		else
		{
			philo_eat(philo);
			if (philo->data_p->is_liv == 0)
				philo_sleep(philo);
			if (philo->data_p->is_liv == 0)
				philo_think(philo);
		}
	}
	return (NULL);
}

//void chk_is_live(t_main *main, t_philo *philos)
//
//{
//
//
//}

int	main(int argc, char **argv)
{
	t_main			*main;
	t_philo			*philos;
	int				cnt;
	int				cnt1;
	int				cnt2;

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
	while (main->is_eat == 0 && main->is_liv == 0)
	{
		cnt1 = -1;
		while (++cnt1 < main->n_philo && main->is_liv == 0)
		{
			cnt2 = 0;
			while (cnt2 < main->n_philo \
			&& philos[cnt2].cnt_eat == main->n_eat)
				cnt2++;
			main->is_eat = (cnt2 == main->n_philo);
			if (cnt2 == main->n_philo)
			{
				main->is_liv = 1;
				main->is_eat = 1;
				break ;
			}
			else if (chk_dead(&philos[cnt1]) == 1)
//			else if ((int)(get_time() - philos[cnt1].time_eat) > main->t_die \
//					&& main->is_liv == 0)
			{
				fn_print(&philos[cnt1], "is DEAD.\033[0m");
				pthread_mutex_lock(&philos->data_p->lock_print);
				main->is_liv = 1;
				main->is_eat = 1;
				pthread_mutex_unlock(&philos->data_p->lock_print);
				break ;
			}
		}
	}
	printf("main_Philo: %i\n", main->n_philo);
	cnt = -1;
	fn_usleep_1(250);
	while (++cnt < main->n_philo)
	{
		printf("n_philo: %i -- cnt: %i\n", main->n_philo, cnt);
		fn_usleep_1(250);
		pthread_join(philos[cnt].thread, NULL);
	}
	fn_clean(main, philos);
	//system("leaks philo");
	return (0);
}
