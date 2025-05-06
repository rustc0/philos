/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmoham <rahmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:10:30 by rahmoham          #+#    #+#             */
/*   Updated: 2025/05/06 10:35:26 by rahmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	start_threads(t_program *program)
{
	int	i;
	pthread_t	t_monitor;

	i = 0;
	pthread_create(&t_monitor, NULL, &monitor, program);
	program->start_time = get_time();
	while (i < program->args->num_philos)
	{
		if ((pthread_create(&program->philos[i].tid, NULL, &routine,
			&program->philos[i])) == -1)
			perror("pthread_create");
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
		if (program->args->num_iterations > 0 &&
			program->philos[i].meal_count >= program->args->num_iterations)
		{
			program->done = 1;
			printf("done : %d\n", program->done);
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
	long	time;
	int	i;

	i = 0;
	pthread_mutex_lock(program->mtx->timelock);
	time = get_time();
	pthread_mutex_unlock(program->mtx->timelock);
	while (i < program->args->num_philos)
	{
		pthread_mutex_lock(program->mtx->timelock);
		if (program->philos[i].last_time &&
			time - program->philos[i].last_time >= program->args->time_to_die)
		{
			pthread_mutex_unlock(program->mtx->timelock);
			pthread_mutex_lock(program->mtx->deadlock);
			program->dead = 1;
			pthread_mutex_unlock(program->mtx->deadlock);
			return (1);
		}
		pthread_mutex_unlock(program->mtx->timelock);
		i++;
	}
	return (0);
}

void	*routine(void *ptr)
{
	t_program	*program;
	t_philo		*philo;

	philo = ptr;
	program = philo->progback;
	while (1)
	{
		if (check_done(program) || check_death(program))
			break ;
		// if (check_death(program))
		// 	break ;
		eat(philo);
		if (check_done(program) || check_death(program))
			break ;
		// if (check_death(program))
		// 	break ;
		ph_sleep(philo);
		if (check_done(program) || check_death(program))
			break ;
		// if (check_death(program))
		// 	break ;
		think(philo);
	}
	return NULL;
}
