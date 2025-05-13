/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmoham <rahmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:10:30 by rahmoham          #+#    #+#             */
/*   Updated: 2025/05/11 13:30:53 by rahmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_program *program)
{
	int			i;
	pthread_t	t_monitor;

	i = 0;
	pthread_create(&t_monitor, NULL, &monitor, program);
	program->start_time = get_time();
	while (i < program->args->num_philos)
	{
		pthread_create(&program->philos[i].tid, NULL, &routine,
			&program->philos[i]);
		i++;
	}
	i = 0;
	while (i < program->args->num_philos)
	{
		pthread_join(program->philos[i].tid, NULL);
		i++;
	}
	pthread_join(t_monitor, NULL);
}

int	check_done(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_lock(program->mtx->donelock);
	pthread_mutex_lock(program->mtx->meallock);
	while (i < program->args->num_philos)
	{
		if (program->args->num_iterations != -1
			&& philos_full(program))
		{
			program->done = 1;
			pthread_mutex_unlock(program->mtx->donelock);
			pthread_mutex_unlock(program->mtx->meallock);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(program->mtx->meallock);
	pthread_mutex_unlock(program->mtx->donelock);
	return (0);
}

int	check_death(t_program *program)
{
	pthread_mutex_lock(program->mtx->deadlock);
	if (program->dead)
	{
		pthread_mutex_unlock(program->mtx->deadlock);
		return (1);
	}
	pthread_mutex_unlock(program->mtx->deadlock);
	return (0);
}

void	*routine(void *ptr)
{
	t_program	*program;
	t_philo		*philo;

	philo = ptr;
	program = philo->progback;
	if (program->args->num_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		eat(philo);
		ph_sleep(philo);
		think(philo);
		if (check_done(program) || check_death(program))
			break ;
	}
	return (NULL);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->progback->mtx->printlock);
	print_message(philo, TAKEN_FORK);
	pthread_mutex_unlock(philo->progback->mtx->printlock);
	ft_msleep(philo->progback->args->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->progback->mtx->printlock);
	print_message(philo, DEAD);
	pthread_mutex_unlock(philo->progback->mtx->printlock);
}
