/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmoham <rahmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:36:50 by rahmoham          #+#    #+#             */
/*   Updated: 2025/05/09 15:50:26 by rahmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dsty_mtx(t_program *program)
{
	pthread_mutex_destroy(program->mtx->printlock);
	pthread_mutex_destroy(program->mtx->timelock);
	pthread_mutex_destroy(program->mtx->deadlock);
	pthread_mutex_destroy(program->mtx->donelock);
	pthread_mutex_destroy(program->mtx->meallock);
	free(program->mtx->printlock);
	free(program->mtx->timelock);
	free(program->mtx->deadlock);
	free(program->mtx->donelock);
	free(program->mtx->meallock);
}

void	clean_up(t_program *program)
{
	if (!program || !program->args)
		return ;
	destroy_forks(program);
	dsty_mtx(program);
	free(program->mtx);
	free(program->philos);
	free(program->args);
	free(program);
}

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

	if (!is_valid(ac, av))
		ft_error("Error: Invalid arguments\n", NULL);
	program = init_program(av);
	start_threads(program);
	clean_up(program);
	return (0);
}
