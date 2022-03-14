/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:23:07 by juasanto          #+#    #+#             */
/*   Updated: 2022/03/14 11:34:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_bzero(void *bzero_string, unsigned int num_char)
{
	unsigned char	*temp_pointer;

	temp_pointer = (unsigned char *)bzero_string;
	while (num_char-- > 0)
		*temp_pointer++ = 0;
	return (bzero_string);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*trgt;

	trgt = malloc(num * size);
	if (!trgt)
		return (NULL);
	ft_bzero(trgt, (num * size));
	return (trgt);
}

int	ft_isdigit(int chr)
{
	return (chr >= 48 && chr <= 57);
}

long long int	ft_atoi(const char *str)
{
	int				sign;
	long long int	result;

	result = 0;
	sign = 0;
	if (*str == '-')
		sign = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit((int)*str))
	{
		if (result < 9223372036854775807)
		{
			result = result * 10 + *str - '0';
			str++;
		}
		else
			return ((sign - 1) * 1);
	}
	if (sign == 1)
		return (-result);
	return (result);
}

void	ft_msgerror(char *str, int errno)
{
	printf("Error\n%s\n", str);
	exit(errno);
}
