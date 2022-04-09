/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:57:08 by juasanto          #+#    #+#             */
/*   Updated: 2022/03/15 15:01:49 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	chk_dead(t_philo *philo)
{
	unsigned long	dead;

	pthread_mutex_lock(&philo->data_p->lock_dead);
	dead = get_time() - philo->time_eat;
	if ((int)dead > philo->data_p->t_die)
	{
		philo->data_p->is_liv = 1;
		pthread_mutex_unlock(&philo->data_p->lock_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data_p->lock_dead);
	return (0);
}

void	pick_fork(t_philo *philo)
{
	if (philo->position == philo->data_p->n_philo)
	{
		pthread_mutex_lock(philo->m_f_l);
		pthread_mutex_lock(philo->m_f_r);
		fn_print(philo, "has taken left fork.\033[0m");
		fn_print(philo, "has taken right fork.\033[0m");
	}
	else
	{
		pthread_mutex_lock(philo->m_f_r);
		pthread_mutex_lock(philo->m_f_l);
		fn_print(philo, "has taken right fork.\033[0m");
		fn_print(philo, "has taken left fork.\033[0m");
	}
}

void	philo_eat(t_philo *philo)
{
	fn_print(philo, "is eating.\033[0m");
	philo->time_eat = get_time();
	fn_usleep_1(philo->data_p->t_eat);
	philo->cnt_eat++;
	pthread_mutex_unlock(philo->m_f_l);
	pthread_mutex_unlock(philo->m_f_r);
}

void	philo_sleep(t_philo *philo)
{
	//incluir resta del tiempo de dormir - tiempo de comer, si es superior
	// esperar el tiempo de comer y morir.
	fn_print(philo, "is sleeping.\033[0m");
	fn_usleep_1(philo->data_p->t_sleep);
}

void	philo_think(t_philo *philo)
{
	int				time_think;

	time_think = (philo->data_p->t_die - (philo->data_p->t_eat + \
			philo->data_p->t_sleep));
	fn_print(philo, "is thinking.\033[0m");
	fn_usleep_1(time_think / 2);
}
