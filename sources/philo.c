/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:09 by juasanto          #+#    #+#             */
/*   Updated: 2022/02/05 10:48:23 by juasanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
/*
** Include para trabajar con semaforos y con hilos
*/

unsigned long long	time_n(t_philo *philos)
{
	unsigned long long		now;

	gettimeofday(&philos->time, NULL);
	now = (philos->time.tv_sec * 1000 + philos->time.tv_usec / 1000);
	return (now);
}

void	*philo_routine(void *arg)
{
	t_philo				*philos;

	philos = arg;
	philos->time_msec = time_n(philos);
	printf("Philo[%i]->thread: %llx - time: %lli\n", \
		philos->position, (unsigned long long )philos->thread, \
		philos->time_msec);
}

int	main(int argc, char **argv)
{
	t_main			*main;
	t_philo			*philos;
	int				cnt;

	cnt = -1;
	main = NULL;
	main = init_main(main, argc, argv);
	chk_args(main);
	philos = ft_calloc(sizeof (t_philo *), main->n_philo);
	while (++cnt < main->n_philo)
	{
		philos[cnt].position = cnt;
		philos[cnt].cnt_eat = 0;
		philos[cnt].fork = cnt;
		usleep(10000);
		pthread_create(&philos[cnt].thread, NULL, &philo_routine,
			&philos[cnt]);
	}
	cnt = -1;
	while (++cnt < main->n_philo)
		pthread_join(philos[cnt].thread, NULL);
	return (0);
}
//	if(0 != pthread_create(&philo1, NULL, prog_philo1, NULL))
//		errorExit("Philo1 cannot be created");
//	if(0 != pthread_create(&philo2, NULL, prog_philo2, NULL))
//		errorExit("Philo2 cannot be created");
//	pthread_join(philo1, NULL);
//	pthread_join(philo2, NULL);
//void	*prog_philo2(void *unused)
//{
//	int		cnt;
//
//	cnt = -1;
//	while (++cnt < 10000)
//	{
//		pthread_mutex_lock(&mutex);
//		count--;
//		pthread_mutex_unlock(&mutex);
//	}
//	return NULL;
//}
