/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmoham <rahmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:08:02 by rahmoham          #+#    #+#             */
/*   Updated: 2025/05/07 13:41:23 by rahmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_program	*init_program(char **av)
{
	t_program	*program;

	program = my_malloc(sizeof(t_program), NULL);
	program->dead = 0;
	program->done = 0;
	program->args = init_args(av, program);
	program->mtx = my_malloc(sizeof(t_mtx), program);
	init_forks(program);
	init_mtx(program, 1);
	init_philos(program);
	return (program);
}

void	init_philos(t_program *program)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = my_malloc(sizeof(t_philo) * program->args->num_philos, program);
	while (i < program->args->num_philos)
	{
		ph[i].progback = program;
		ph[i].id = i + 1;
		ph[i].last_time = get_time();
		ph[i].tid = 0;
		ph[i].meal_count = 0;
		ph[i].left_fork = &program->forks[i];
		if (program->args->num_philos > 1)
		{
			if (ph[i].id + 1 > program->args->num_philos)
				ph[i].right_fork = &program->forks[0];
			else
				ph[i].right_fork = &program->forks[i + 1];
		}
		// printf("philo %d left fork %p right fork %p\n", ph[i].id,
		// 	ph[i].left_fork, ph[i].right_fork);
		i++;
	}
	program->philos = ph;
}

void	init_mtx(t_program *program, int flag)
{
	if (flag)
	{
		program->mtx->printlock = my_malloc(sizeof(pthread_mutex_t), program);
		program->mtx->timelock = my_malloc(sizeof(pthread_mutex_t), program);
		program->mtx->meallock = my_malloc(sizeof(pthread_mutex_t), program);
		program->mtx->deadlock = my_malloc(sizeof(pthread_mutex_t), program);
		program->mtx->donelock = my_malloc(sizeof(pthread_mutex_t), program);
		pthread_mutex_init(program->mtx->printlock, NULL);
		pthread_mutex_init(program->mtx->timelock, NULL);
		pthread_mutex_init(program->mtx->deadlock, NULL);
		pthread_mutex_init(program->mtx->donelock, NULL);
		pthread_mutex_init(program->mtx->meallock, NULL);
	}
	else
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
}

void	init_forks(t_program *program)
{
	int	i;
	int	nph;

	nph = program->args->num_philos;
	program->forks = my_malloc(sizeof(pthread_mutex_t) * nph, program);
	i = 0;
	while (i < nph)
	{
		pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}
}

t_args	*init_args(char **args, t_program *program)
{
	t_args	*p_args;

	p_args = my_malloc(sizeof(t_args), program);
	p_args->num_philos = ft_atol(args[1]);
	p_args->time_to_die = ft_atol(args[2]);
	p_args->time_to_eat = ft_atol(args[3]);
	p_args->time_to_sleep = ft_atol(args[4]);
	if (args[5])
		p_args->num_iterations = ft_atol(args[5]);
	else
		p_args->num_iterations = -1;
	if(p_args->num_philos == 0)
	{
		free(p_args);
		free(program);
		ft_error("Error: Invalid arguments\n", program);
	}
	if (p_args->num_philos == -1 || p_args->time_to_die == -1
		|| p_args->time_to_eat == -1 || p_args->time_to_sleep == -1)
		ft_error("Error: Invalid arguments\n", program);
	return (p_args);
}
