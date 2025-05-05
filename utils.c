/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmoham <rahmoham@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 15:38:01 by rahmoham          #+#    #+#             */
/*   Updated: 2025-05-05 15:38:01 by rahmoham         ###   ########`         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str, t_program *program)
{
	write(2, str, ft_strlen(str));
	clean_up(program);
	exit(1);
}

int	is_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' && str[i + 1] <= '9' && str[i + 1] >= '0')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

long	ft_atol(char *str)
{
	int		i;
	int		n;
	long	ret;

	i = 0;
	n = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		if (ret * n > UINT_MAX || ret * n < 0)
			return (-1);
		i++;
	}
	return (ret * n);
}

void	*my_malloc(size_t size, t_program *program)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_error("alloction error", program);
	return (ptr);
}
