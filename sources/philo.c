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

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(size_t time_in_ms)
{
	size_t	start_time;

	start_time = get_time();
	usleep((time_in_ms - 10) * 1000);
	while ((get_time() - time_in_ms) < start_time)
		;
}

void	pick_fork(t_philo *n_philo)
{
	t_philo			*philo;

	philo = n_philo;

	pthread_mutex_lock(&philo->m_f_l);
	pthread_mutex_lock(&philo->m_f_r);
	pthread_mutex_lock(&philo->m_fork);
	philo->f_r = philo->position;
	if ((philo->position - 1) >= 0)
		philo->f_l = philo->position - 1;
	pthread_mutex_unlock(&philo->m_f_l);
	pthread_mutex_unlock(&philo->m_f_r);
	pthread_mutex_unlock(&philo->m_fork);

}

void	*philo_routine(void *n_philo)
{
	t_philo 		*philo;

	philo = n_philo;
	philo->time_start = get_time();
	pick_fork(philo);
	if (philo->f_r < 0 || philo->f_l < 0)
			pthread_exit(NULL);
	ft_usleep(philo->time_eat);
	printf("Philo %i is eating for %li\n", philo->position, get_time() -
	philo->time_start);
	pthread_exit(NULL);
}

void	init_philos(t_main *main)
{
	int		cnt;

	cnt = -1;
	while (++cnt < main->n_philo)
	{
		main->philos[cnt].position = cnt;
		main->philos[cnt].cnt_eat = 0;
		main->philos[cnt].fork = 0;
		main->philos[cnt].f_l = main->n_philo;
		main->philos[cnt].f_r = -1;
		main->philos[cnt].time_eat = main->t_eat;
		pthread_mutex_init(&main->philos[cnt].m_f_l, NULL);
		pthread_mutex_init(&main->philos[cnt].m_f_r, NULL);
		pthread_mutex_init(&main->philos[cnt].m_fork, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_main			*main;
	int				cnt;
	long			time;

	cnt = -1;
	main = NULL;
	main = init_main(main, argc, argv);
	chk_args(main);
	main->philos = ft_calloc(sizeof (t_philo *), main->n_philo);
	init_philos(main);
	while (++cnt < main->n_philo)
	{
		pthread_create(&main->philos[cnt].thread, NULL, &philo_routine,
			&main->philos[cnt]);
	}
	cnt = -1;
	while (++cnt < main->n_philo)
		pthread_join(main->philos[cnt].thread, NULL);
	cnt = -1;
	time = get_time();
	while(++cnt < main->n_philo)
	{
		printf("Philo[%i].thread: %llx - sec: %li ------ f-l: %i - f-r: %i\n",
		main->philos[cnt].position,
		(unsigned long long ) main->philos[cnt].thread, \
		(time - main->philos[cnt].time_start), main->philos[cnt].f_l,
		main->philos[cnt].f_r);
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
