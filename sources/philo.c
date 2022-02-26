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

void	fn_usleep(size_t time_in_ms)
{
	unsigned long		start_time;

	start_time = get_time();
	usleep((time_in_ms - 10) * 1000);
	while ((get_time() - time_in_ms) < start_time)
			;
}

void	fn_usleep_1(size_t time_in_ms)
{
	unsigned long		start_time;

	start_time = get_time();
	while (get_time() < (time_in_ms + start_time))
		usleep(500);
}

void	fn_print(t_philo *philo, char *task, int time)
{
	pthread_mutex_lock(&philo->data_p.lock_gen);
	printf("Philo[%i] is %s for %i ms\n", philo->position, task, time);
	pthread_mutex_unlock(&philo->data_p.lock_gen);
}

void	pick_fork(t_philo *n_philo)
{
	t_philo			*philo;
	int				cnt;
	unsigned long	time;

	cnt = -1;
	time = 0;
	philo = n_philo;
	if(philo->position % 2 == 0)
		fn_usleep(500);
	philo->time_start = get_time();

	if (pthread_mutex_lock(&philo->m_f_l) == 0)
			printf("l - ok\n");
	if (pthread_mutex_lock(&philo->m_f_r) == 0)
			printf("r - ok\n");
	fn_print(philo, "Take forks", 0);
	fn_usleep(2500);
	pthread_mutex_unlock(&philo->m_f_l);
	pthread_mutex_unlock(&philo->m_f_r);
	pthread_mutex_lock(&philo->m_f_l);
	pthread_mutex_lock(&philo->m_f_r);
	fn_usleep(philo->data_p.t_eat);
	fn_print(philo, "Eating", (int)(get_time() - philo->time_start));
	pthread_mutex_unlock(&philo->m_f_l);
	pthread_mutex_unlock(&philo->m_f_r);




}

void	*philo_routine(void *n_philo)
{
	t_philo 		*philo;

	philo = n_philo;
	philo->time_start = get_time();
	pick_fork(philo);
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
		fn_usleep(500);
		pthread_create(&philos[cnt].thread, NULL, &philo_routine,
			&philos[cnt]);
	}
	cnt = -1;
	while (++cnt < main->n_philo)
		pthread_join(philos[cnt].thread, NULL);
	cnt = -1;
	time = get_time();
	return (0);
}

