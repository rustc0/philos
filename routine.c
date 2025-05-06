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
	if (check_done(philo->progback))
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
	if (check_done(philo->progback))
		return ;
	pthread_mutex_lock(philo->progback->mtx->printlock);
	print_message(philo, SLEPT);
	pthread_mutex_unlock(philo->progback->mtx->printlock);
	ft_msleep(philo->progback->args->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (check_done(philo->progback))
		return ;
	pthread_mutex_lock(philo->progback->mtx->printlock);
	print_message(philo, THOUGHT);
	pthread_mutex_unlock(philo->progback->mtx->printlock);
}
