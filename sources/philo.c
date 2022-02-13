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
 * Each putstr/putnbr makes (at least) one write syscall.
 * Each syscall takes quite a lot of time, so you'll get the best performance
 * writing all the info to a buffer and printing it out in a single write().
*/

/*
unsigned long long	time_n(t_philo *philos)
{
	unsigned long long		now;

	gettimeofday(&philos->time, NULL);
	now = (philos->time.tv_sec * 1000 + philos->time.tv_usec / 1000);
	return (now);
}
*/

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	*philo_routine(void *arg)
{
	t_philo				*philos;

	usleep(2);
	philos = arg;
	philos->time_msec = get_time();
	philos->f_r = philos->position;
	if ((philos->position - 1) >= 0)
		philos->f_l = philos->position - 1;
	printf("Philo[%i]->thread: %llx - time: %lli\n", philos->position, \
	(unsigned long long )philos->thread, philos->time_msec);
	pthread_exit(NULL);
}

void	init_philos(t_philo *philos, int n_philo)
{
	int		cnt;

	cnt = -1;
	while (++cnt < n_philo)
	{
		philos[cnt].position = cnt;
		philos[cnt].cnt_eat = 0;
		philos[cnt].fork = cnt;
		philos[cnt].f_l = n_philo;
	}
}

int	main(int argc, char **argv)
{
	t_main			*main;
	t_philo			*philos;
	int				cnt;
	long			time;

	cnt = -1;
	main = NULL;
	main = init_main(main, argc, argv);
	chk_args(main);
	philos = ft_calloc(sizeof (t_philo *), main->n_philo);
	init_philos(philos, main->n_philo);
	while (++cnt < main->n_philo)
	{
		usleep(100 * 1000);
		pthread_create(&philos[cnt].thread, NULL, &philo_routine,
			&philos[cnt]);
	}
	cnt = -1;
	while (++cnt < main->n_philo)
		pthread_join(philos[cnt].thread, NULL);
	cnt = -1;
	time = get_time();
	while(++cnt < main->n_philo)
	{
		printf("Philo[%i].thread: %llx - sec: %li ------ f-l: %i - f-r: %i\n",
		philos[cnt].position,
		(unsigned long long ) philos[cnt].thread, \
		(time - philos[cnt].time_msec), philos[cnt].f_l, philos[cnt].f_r);
	}
	return (0);
}
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
