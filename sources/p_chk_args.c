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

int	chk_args(t_main *philo)
{
	int		cnt;

	cnt = 0;
	while (++cnt < philo->argc)
		printf("argv[%i]=%s\n", cnt, philo->argv[cnt]);
	if (philo->n_philo <= 0 || philo->t_die <= 0 || philo->t_eat <= 0 \
		|| philo->t_sleep <= 0 || philo->m_eat <= 0)
		ft_msgerror("Cagada total con los números\n", -1);
	return (0);
}
