/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:09 by juasanto          #+#    #+#             */
/*   Updated: 2022/02/03 12:40:14 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
/*
** Include para trabajar con semaforos y con hilos
*/
static	int	count = 10;
pthread_mutex_t		mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned long long	time_n(t_main *main)
{
	now = (main->time.tv_sec * 1000 + main->time.tv_usec / 1000)
	return(now);
}

void	*prog_philo1(void *unused)
{

	int		cnt;

	cnt = -1;
	while (++cnt < 10000)
	{
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void	*prog_philo2(void *unused)
{
	int		cnt;

	cnt = -1;
	while (++cnt < 10000)
	{
		pthread_mutex_lock(&mutex);
		count--;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void	errorExit(char *strerr)
{
	perror(strerr);
	exit(1);
}


int	main(int argc, char **argv)
{
	t_main			*main;
	t_philo			*philos;
	int				cnt;

	struct timeval	time;
	pthread_t		philo1;
	pthread_t		philo2;

	cnt = -1;
	main = NULL;
	main = init_main(main, argc, argv);
	chk_args(main);
	philos = ft_calloc(sizeof (t_philo), main->n_philo);
	while(++cnt < main->n_philo)
	{
		philos[cnt].position = cnt;
		philos[cnt].time_msec = time_n(main);
		philos[cnt].fork = cnt;
	}


	if(0 != pthread_create(&philo1, NULL, prog_philo1, NULL))
		errorExit("Philo1 cannot be created");
	if(0 != pthread_create(&philo2, NULL, prog_philo2, NULL))
		errorExit("Philo2 cannot be created");
	pthread_join(philo1, NULL);
	pthread_join(philo2, NULL);

	gettimeofday (&time, NULL);
	printf("* %li\n", (time.tv_sec * 1000 + time.tv_usec / 1000));
	printf("Valor de count: %d\n", count);

	return (0);
}
