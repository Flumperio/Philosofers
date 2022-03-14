/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_chk_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:17:10 by juasanto          #+#    #+#             */
/*   Updated: 2022/03/14 11:34:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	chk_args(t_main *main)
{
	int		cnt;

	cnt = 0;
	if (main->n_philo <= 0 || main->t_die <= 0 || main->t_eat <= 0 \
		|| main->t_sleep <= 0 || \
		(main->argc == 6 && main->n_eat <= 0))
		ft_msgerror("Valores no validos.\n", -1);
	return (0);
}

void	fn_clean(t_main *main, t_philo *philo)
{
	int			cnt;

	cnt = -1;
	while (++cnt < main->n_philo)
		pthread_mutex_destroy(&main->lock_fork[cnt]);
	pthread_mutex_destroy(&main->lock_print);
	pthread_mutex_destroy(&main->lock_gen);
	free (main->lock_fork);
	free (philo);
	free (main);
}

void	fn_print(t_philo *philo, char *task)
{
	unsigned long		time;
	int					color;

	color = 30 + philo->position;
	pthread_mutex_lock(&philo->data_p->lock_print);
	time = get_time() - philo->data_p->time_start;
	printf("%lims \033[%imPhilo{%i} %s\n", time, color, philo->position, task);
	pthread_mutex_unlock(&philo->data_p->lock_print);
}
