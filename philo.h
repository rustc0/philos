/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmoham <rahmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:37:42 by rahmoham          #+#    #+#             */
/*   Updated: 2025/05/09 10:34:38 by rahmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <limits.h>

# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define RESET   "\033[0m"

# define TAKEN_FORK		GREEN "%ld %d has taken a fork\n" RESET
# define EATING			"%ld %d is eating\n"
# define SLEEPING		"%ld %d is sleeping\n"
# define THINKING		"%ld %d is thinking\n"
# define DEAD			RED "%ld %d died\n" RESET

// enum	pprint
// {
// 	TOOK,
// 	EAT,
// 	SLEPT,
// 	THOUGHT,
// 	DIED,
// };

typedef pthread_mutex_t	t_mtxlck;

typedef struct s_args
{
	long	num_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_iterations;
}	t_args;

typedef	struct s_mtx
{
	t_mtxlck	*printlock;
	t_mtxlck	*timelock;
	t_mtxlck	*deadlock;
	t_mtxlck	*donelock;
	t_mtxlck	*meallock;
}	t_mtx;

typedef struct s_philo
{
	struct s_program	*progback;
	pthread_t			tid;
	t_mtxlck			*right_fork;
	t_mtxlck			*left_fork;
	long 				last_time;
	long				meal_count;
	int					id;
}	t_philo;

typedef struct s_program
{
	t_mtxlck		*forks;
	t_philo			*philos;
	t_args			*args;
	t_mtx			*mtx;
	long			start_time; //
	int				done;
	int				dead;
}	t_program;

// Utility functions

void	ft_error(char *str, t_program *program);
long	ft_atol(char *str);
int		is_digits(char *str);
int		ft_strlen(char *str);
void	*my_malloc(size_t size, t_program *program);

// other utility functions

void	clean_up(t_program *program);
void	destroy_forks(t_program *program);
void	safe_lock(t_philo *philo, int flag);
void	print_message(t_philo *philo, char *flag);
long	get_time(void);
int		ft_msleep(unsigned int time);
int		check_done(t_program *program);
int		check_death(t_program *program);


// Initialization functions

t_args		*init_args(char **args, t_program *program);
void		init_forks(t_program *program);
void		init_mtx(t_program *program, int flag);
void		init_philos(t_program *program);
t_program	*init_program(char **av);

// Thread functions

void	start_threads(t_program *program);
void	*routine(void *ptr);
void	eat(t_philo *philo);
void	ph_sleep(t_philo *philo);
void	think(t_philo *philo);
void	*monitor(void *ptr);
void	one_philo(t_philo *philo);

#endif