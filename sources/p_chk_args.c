/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_chk_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:17:10 by juasanto          #+#    #+#             */
/*   Updated: 2022/01/17 16:19:38 by juasanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	chk_args(t_main *main)
{
	int		cnt;

	cnt = 0;
	while (++cnt < main->argc)
		printf("argv[%i]=%s\n", cnt, main->argv[cnt]);
	if (main->n_philo <= 0 || main->t_die <= 0 || main->t_eat <= 0 \
		|| main->t_sleep <= 0 || \
		(main->argc == 6 && main->m_eat <= 0))
		ft_msgerror("Valores no validos.\n", -1);
	return (0);
}
