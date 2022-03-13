/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:09 by juasanto          #+#    #+#             */
/*   Updated: 2022/03/13 12:59:23 by juasanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	one_philo(t_philo *philo)
{
	printf("0ms Philo[1] [32mhas taken right fork.[0m\n");
	fn_usleep_1(philo->data_p->t_die);
	printf("%ims Philo[1] [35mis Dead.[0m\n", philo->data_p->t_die);
	philo->data_p->is_alive = 1;
}

void	*philo_routine(void *n_philo)
{
	t_philo			*philo;

	philo = (t_philo *)n_philo;
	if (philo->data_p->n_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->position % 2 == 0)
		fn_usleep_1(2);
	while (philo->cnt_eat != philo->data_p->n_eat && \
		philo->data_p->is_alive == 0)
	{
		if (philo->data_p->is_alive == 0)
			philo_eat(philo);
		if (philo->data_p->is_alive == 0)
			philo_sleep(philo);
		if (philo->data_p->is_alive == 0)
			philo_think(philo);
	}
	return (NULL);
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
	while (++cnt < main->n_philo)
		pthread_create(&philos[cnt].thread, NULL, &philo_routine, \
			&philos[cnt]);
	cnt = -1;
	while (++cnt < main->n_philo)
		pthread_join(philos[cnt].thread, NULL);
	fn_clean(main, philos);
	system("leaks philo");
	return (0);
}
