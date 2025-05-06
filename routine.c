/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmoham <rahmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:43:03 by rahmoham          #+#    #+#             */
/*   Updated: 2025/05/06 08:28:47 by rahmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo	*philo)
{
	if (check_done(philo->progback) || check_death(philo->progback))
		return ;
	safe_lock(philo, 0);
	pthread_mutex_lock(philo->progback->mtx->printlock);
	print_message(philo, TOOK);
	print_message(philo, TOOK);
	print_message(philo, EAT);
	pthread_mutex_unlock(philo->progback->mtx->printlock);
	ft_msleep(philo->progback->args->time_to_eat);
	safe_lock(philo, 1);
	pthread_mutex_lock(philo->progback->mtx->timelock);
	philo->last_time = get_time();
	pthread_mutex_unlock(philo->progback->mtx->timelock);
	pthread_mutex_lock(philo->progback->mtx->meallock);
	philo->meal_count++;
	pthread_mutex_unlock(philo->progback->mtx->meallock);
}

void	ph_sleep(t_philo *philo)
{
	if (check_done(philo->progback) || check_death(philo->progback))
		return ;
	pthread_mutex_lock(philo->progback->mtx->printlock);
	print_message(philo, SLEPT);
	pthread_mutex_unlock(philo->progback->mtx->printlock);
	ft_msleep(philo->progback->args->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (check_done(philo->progback) || check_death(philo->progback))
		return ;
	pthread_mutex_lock(philo->progback->mtx->printlock);
	print_message(philo, THOUGHT);
	pthread_mutex_unlock(philo->progback->mtx->printlock);
}

void	*monitor(void *ptr)
{
	t_program	*program;
	int			i;

	program = (t_program *)ptr;
	i = 0;
	while (1)
	{
		if (check_done(program))
			break ;
		if (i >= program->args->num_philos)
			i = 0;
		pthread_mutex_lock(program->mtx->timelock);
		if (program->philos[i].last_time &&
			get_time() - program->philos[i].last_time >= program->args->time_to_die)
		{
			pthread_mutex_unlock(program->mtx->timelock);
			print_message(&program->philos[i], DIED);
			pthread_mutex_lock(program->mtx->deadlock);
			program->dead = 1;
			printf("dead = %d\n\n", program->dead);
			pthread_mutex_unlock(program->mtx->deadlock);
			return NULL;
		}
		pthread_mutex_unlock(program->mtx->timelock);
		i++;
		ft_msleep(10);
	}
	return NULL;
}