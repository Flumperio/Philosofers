/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:09 by juasanto          #+#    #+#             */
/*   Updated: 2022/02/21 13:34:46 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
/*
** Include para trabajar con semaforos y con hilos
 * Each putstr/putnbr makes (at least) one write syscall.
 * Each syscall takes quite a lot of time, so you'll get the best performance
 * writing all the info to a buffer and printing it out in a single write().
*/

unsigned long	get_time(void)
{
	struct timeval	tp;
	unsigned long	milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(size_t time_in_ms)
{
	unsigned long		start_time;

	start_time = get_time();
	usleep((time_in_ms - 10) * 1000);
	while ((get_time() - time_in_ms) < start_time)
			;
}

void	ft_usleep_1(size_t time_in_ms)
{
	unsigned long		start_time;

	start_time = get_time();
	while (get_time() < (time_in_ms + start_time))
		usleep(500);
}

void	fn_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_p.lock_gen);
	printf("Philo[%i], %lli\n", philo->position, philo->thread);
	pthread_mutex_unlock(&philo->data_p.lock_gen);
}

void	pick_fork(t_philo *n_philo)
{
	t_philo *philo;
	int				cnt;

	cnt = -1;
	philo = n_philo;
	fn_print(philo);
}

void	*philo_routine(void *n_philo)
{
	t_philo 		*philo;

	philo = n_philo;
	philo->time_start = get_time();
	pick_fork(philo);
	if (philo->f_r < 0 || philo->f_l < 0)
			pthread_exit(NULL);
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	t_main			*main;
	t_philo			*philos;
	int				cnt;
	unsigned long			time;

	cnt = -1;
	main = NULL;
	philos = NULL;
	main = init_main(main, argc, argv);
	chk_args(main);
	philos = init_philo(philos, main);
	main->lock_fork = init_fork(main->lock_fork, main, philos);
	while (++cnt < main->n_philo)
	{
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
		(time - philos[cnt].time_start), philos[cnt].f_l,
		philos[cnt].f_r);
	}
	return (0);
}

