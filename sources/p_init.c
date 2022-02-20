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

t_main	*init_main(t_main *main, int argc, char **argv)
{
	main = ft_calloc(sizeof (t_main), 1);
	main->argc = argc;
	main->argv = argv;
	if (main->argc < 5 || main->argc > 6)
		ft_msgerror("Numero de opciones invalidas.\
		\nSolo se admiten numeros como parametros\
		\nEjemplo: ./main n1 n2 n3 n4 n5\n", -1);
	main->n_philo = (int)ft_atoi(main->argv[1]);
	main->t_die = (int)ft_atoi(main->argv[2]);
	main->t_eat = (int)ft_atoi(main->argv[3]);
	main->t_sleep = (int)ft_atoi(main->argv[4]);
	if (main->argc == 6)
		main->n_eat = (int)ft_atoi(main->argv[5]);
	return (main);
}
