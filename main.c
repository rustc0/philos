/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmoham <rahmoham@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 15:36:50 by rahmoham          #+#    #+#             */
/*   Updated: 2025-05-05 15:36:50 by rahmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

int	is_valid(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (!is_digits(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_program	*program;
	char		*str;

	str = "Usage: philos_n death_t eating_t sleeping_t [iterations]\n";
	if (!is_valid(ac, av))
		ft_error(str, NULL);
	program = init_program(av);

	start_threads(program);

	clean_up(program);
	return (0);
}
