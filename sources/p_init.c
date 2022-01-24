/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:23:05 by juasanto          #+#    #+#             */
/*   Updated: 2022/01/17 16:19:35 by juasanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_main	*init_philo(t_main *philo, int argc, char **argv)
{
	philo = ft_calloc(sizeof (t_main), 1);
	philo->argc = argc;
	philo->argv = argv;
	if (philo->argc < 5 || philo->argc > 6)
		ft_msgerror("Numero de opciones invalidas.\
		\nSolo se admiten numeros como parametros\
		\nEjemplo: ./philo n1 n2 n3 n4 n5\n", -1);
	philo->n_philo = (int)ft_atoi(philo->argv[1]);
	philo->t_die = (int)ft_atoi(philo->argv[2]);
	philo->t_eat = (int)ft_atoi(philo->argv[3]);
	philo->t_sleep = (int)ft_atoi(philo->argv[4]);
	philo->m_eat = (int)ft_atoi(philo->argv[5]);
	return (philo);
}
