/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:09 by juasanto          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/10 13:55:41 by                  ###   ########.fr       */
=======
/*   Updated: 2022/03/07 18:11:07 by juasanto         ###   ########.fr       */
>>>>>>> 5043259b4989591bb63ff511717a922e09b7df3d
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

void	fn_print(t_philo *philo, char *task)
{
	unsigned long		time;

	pthread_mutex_lock(&philo->data_p->lock_print);
	time = get_time() - philo->data_p->time_start;
	printf("%lims Philo[%i] %s\n", time, philo->position, task);
	pthread_mutex_unlock(&philo->data_p->lock_print);
}

void	pick_fork(t_philo *philo)
{
	if(philo->position == philo->data_p->n_philo && philo->data_p->n_philo != 1)
	{
		pthread_mutex_lock(philo->m_f_l);
		fn_print(philo, "\033[32mhas taken left fork.\033[0m");
		pthread_mutex_lock(philo->m_f_r);
		fn_print(philo, "\033[32mhas taken right fork.\033[0m");
	}
	else
	{
		pthread_mutex_lock(philo->m_f_r);
		fn_print(philo, "\033[32mhas taken right fork.\033[0m");
		pthread_mutex_lock(philo->m_f_l);
		fn_print(philo, "\033[32mhas taken left fork.\033[0m");
	}
}

void	philo_eat(t_philo *philo)
{
	int			dead;

	dead = get_time() - philo->time_eat;
	if(dead > philo->data_p->t_die)
	{
		philo->data_p->is_alive = 1;
		printf("Dead: %i -- Time_die: %i\n", dead, philo->data_p->t_die);
	}

	pick_fork(philo);
	pthread_mutex_lock(&philo->data_p->lock_gen);
	fn_print(philo, "\033[31mis eating.\033[0m");
	philo->time_eat = get_time();
	pthread_mutex_unlock(&philo->data_p->lock_gen);
	fn_usleep_1(philo->data_p->t_eat);
	philo->cnt_eat++;
	pthread_mutex_unlock(philo->m_f_l);
	pthread_mutex_unlock(philo->m_f_r);
}

void	philo_sleep(t_philo *n_philo)
{
	t_philo			*philo;

	philo = n_philo;
	fn_print(philo, "\033[36mis sleeping.\033[0m");
	fn_usleep_1(philo->data_p->t_sleep);
}

void	philo_think(t_philo *n_philo)
{
	t_philo			*philo;

	philo = n_philo;
	fn_print(philo, "\033[33mis thinking.\033[0m");
	fn_usleep_1(philo->data_p->t_sleep);
}

void	*philo_routine(void *n_philo)
{
	t_philo 		*philo;

	philo = (t_philo *)n_philo;
	if(philo->data_p->n_philo == 1)
	{
		printf("0ms Philo[1] [32mhas taken right fork.[0m\n");
		fn_usleep_1(philo->data_p->t_die);
		printf("%ims Philo[1] [35mis Dead.[0m\n", philo->data_p->t_die);
		philo->data_p->is_alive = 1;
		return (NULL);
	}
	if(philo->position % 2 == 0)
		fn_usleep_1(2);
	while (philo->data_p->is_alive == 0)
	{
		if(philo->cnt_eat != philo->data_p->n_eat)
			philo_eat(philo);
		if(philo->cnt_eat != philo->data_p->n_eat)
			philo_sleep(philo);
		if(philo->cnt_eat != philo->data_p->n_eat)
			philo_think(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_main			*main;
	t_philo			*philos;
	int				cnt;
	//unsigned long			time;

	cnt = -1;
	main = NULL;
	philos = NULL;
	main = init_main(main, argc, argv);
	chk_args(main);
	init_fork(main);
	philos = init_philo(philos, main);
	while (++cnt < main->n_philo)
	{
		pthread_create(&philos[cnt].thread, NULL, &philo_routine,
			&philos[cnt]);
	}
	cnt = -1;
	while (main->is_alive == 0)
	{
		cnt = -1;
		while (++cnt < main->n_philo)
		{
			if(philos[cnt].cnt_eat == main->n_eat)
				return(123);
		}
	}
	cnt = -1;
	while (++cnt < main->n_philo)
		
		// destruir los mutex.
		pthread_join(philos[cnt].thread, NULL);
		// Liberar memoria.
	return (0);
}

