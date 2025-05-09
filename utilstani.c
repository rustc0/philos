/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilstani.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmoham <rahmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:07:36 by rahmoham          #+#    #+#             */
/*   Updated: 2025/05/09 13:06:23 by rahmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_program *program)
{
	if (!program || !program->args)
		return ;
	destroy_forks(program);
	init_mtx(program, 0);
	free(program->mtx);
	free(program->philos);
	free(program->args);
	free(program);
}

void	destroy_forks(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args->num_philos)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	free(program->forks);
}

int	ft_msleep(unsigned int time)
{
	time_t		strt;

	strt = get_time();
	while (1)
	{
		if (get_time() - strt >= time)
			break ;
		usleep(100);
	}
	return (0);
}

void	safe_lock(t_philo *philo, int flag)
{
	int (i), (j);
	if (!flag)
	{
		if (philo->id % 2 == 0)
		{
			i = pthread_mutex_lock(philo->left_fork);
			j = pthread_mutex_lock(philo->right_fork);
		}
		else
		{
			i = pthread_mutex_lock(philo->right_fork);
			j = pthread_mutex_lock(philo->left_fork);
		}
	}
	else
	{
		i = pthread_mutex_unlock(philo->left_fork);
		j = pthread_mutex_unlock(philo->right_fork);
	}
	if (i != 0 || j != 0)
		ft_error("Error: Mutex lock or unnlock failed\n", philo->progback);
}

void	print_message(t_philo *philo, char *flag)
{
	long	timestrt;

	if (check_done(philo->progback) || check_death(philo->progback))
		return ;
	timestrt = philo->progback->start_time;
	printf(flag, get_time() - timestrt, philo->id);
}

int	philos_full(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args->num_philos)
	{
		if (program->philos[i].meal_count < program->args->num_iterations)
			return (0);
		i++;
	}
	return (1);
}
