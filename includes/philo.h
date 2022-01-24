/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:02:29 by juasanto          #+#    #+#             */
/*   Updated: 2022/01/17 16:19:38 by juasanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
 ** Libraries
*/
# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>

/*
** Aux Structures
*/

/*
** Main Structures
*/

typedef struct s_main
{
	int		argc;
	char	**argv;
	int		tmp;
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		m_eat;
}			t_main;

/*
** Funtions
*/
t_main	*init_philo(t_main *philo, int argc, char **argv);
int		chk_args(t_main *philo);

/*
** Aux Funtions
*/
void	*ft_calloc(size_t num, size_t size);
long long int	ft_atoi(const char *str);
void	ft_msgerror(char *str, int errno);
#endif
