/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_chk_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:17:10 by juasanto          #+#    #+#             */
/*   Updated: 2022/04/12 14:06:21 by juasanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	chk_args(t_main *main)
{
	if (main->n_philo <= 0 || main->t_die <= 0 || main->t_eat <= 0 \
		|| main->t_sleep <= 0 || \
		(main->argc == 6 && main->n_eat <= 0) || \
		main->n_philo > 200)
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
	if (fn_chk_live(philo) == 0)
		printf("%lims \033[%imPhilo{%i} %s\n", time, color, \
						philo->position, task);
	pthread_mutex_unlock(&philo->data_p->lock_print);
}

int	fn_no_chars(const char *str)
{
	while (*str)
	{
		if (ft_isdigit((int)*str) == 0)
			return (-1);
		str++;
	}
	return (1);
}

int	fn_chk_live(t_philo *philos)
{
	int	retval;

	pthread_mutex_lock(&philos->data_p->lock_think);
	retval = philos->data_p->is_liv;
	pthread_mutex_unlock(&philos->data_p->lock_think);
	return (retval);
}
