/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:23:05 by juasanto          #+#    #+#             */
/*   Updated: 2022/01/15 13:28:30 by juasanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_main		*init_philo(t_main *philo, int argc, char **argv)
{
	philo = malloc(sizeof(t_main) * 1);
	*philo = NULL;
	philo->argc = argc;
	philo->argv = argv;
	return (philo);
}
