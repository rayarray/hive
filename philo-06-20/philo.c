/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:30:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/20 17:30:20 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chk_args(int ac, char **ag)
{
	//printf("ac:%d [%d]\n", ac, read_args(ag, 5));
	if (ac < 5 || ac > 6)
	{
		printf("Usage: philos a b c d [e]\n");
		printf("Where a is the number of philosophers, b is the time they can survive between\n");
		printf("meals (counted from the start of the meal), c is the time it takes to eat\n");
		printf("and d is the time it takes to sleep. Optionally [e] can be specified as the\n");
		printf("number of meals each philosopher can eat before stopping\n");
		return (-1);
	}
	if (read_args(ag, 1) == -1 || read_args(ag, 2) == -1 || read_args(ag, 3) == -1 || read_args(ag, 4) == -1)
	{
		printf("Invalid argument. Numeric values [0-9] only!\n");
		return (-1);
	}
	if (ac == 6 && read_args(ag, 5) == -1)
	{
		printf("Invalid argument. Numeric values [0-9] only!\n");
		return (-1);
	}
	return (1);
}

void	*philosopher_old(void *arg)
{
	struct timeval	tv;
	int				i;

	(void)arg;
	i = 0;
	while (i < 200)
	{
		pthread_mutex_lock((pthread_mutex_t *)arg);
		i++;
		pthread_mutex_unlock((pthread_mutex_t *)arg);
		usleep(i);
	}
	gettimeofday(&tv, NULL);
	printf("Thread exiting at %lds%dms\n", tv.tv_sec, tv.tv_usec);
	pthread_exit(NULL);
}

void	*philosopher(void *arg)
{
	t_pdata	*brain;

	brain = arg;
	gettimeofday(&(brain->start), NULL);
	gettimeofday(&(brain->lastmeal), NULL);
	while (*(brain->death) == 0)
	{
		add_log_msg(brain, " started thinking\n", NULL);
		manage_forks(brain, 1);
		if (get_ms_diff(&brain->lastmeal, &brain->now, 1) > brain->starve)
		{
			add_log_msg(brain, " DIED\n", NULL);
			*(brain->death) = brain->name;
			//manage_forks(brain, 0);
			pthread_exit(NULL);
		}
		gettimeofday(&(brain->lastmeal), NULL);
		add_log_msg(brain, " started eating the ", "th meal\n");
		rsleep(brain->eat_dur);
		manage_forks(brain, 0);
		if (brain->meals == brain->full)
			break ;
		add_log_msg(brain, " started sleeping\n", NULL);
		rsleep(brain->slp_dur);
	}
	if (brain->meals == brain->full)
		add_log_msg(brain, " is sated", NULL);
	pthread_exit(NULL);
}

int	commence_philosophy(int size, pthread_t *philos, pthread_mutex_t **forks,
	t_pdata *brains)
{
	int					result;
	int					i;

	i = -1;
	printf("break\n");
	while (++i <= size)
	{
		printf("mtxinit%d size:%d\n", i, size);
		result = pthread_mutex_init(forks[i], NULL);
		if (result)
			printf("Mutex creation error %d\n", result);
	}
	usleep(5000);
	i = 0;
	while (++i < size)
	{
		printf("mkb %d\n", i);
		make_brain(i, brains, forks, 0);
	}
	make_brain(i, brains, forks, 1);
	i = 0;
	while (++i <= size)
	{
		result = pthread_create(philos + i, NULL, philosopher, brains + i);
		if (result)
			printf("Thread creation failed\n");
		result = pthread_detach(*(philos + i));
		if (result)
			printf("Thread detach failed\n");
	}
	return (1);
}

int	main(int ac, char **ag)
{
	pthread_t			*philos;
	pthread_mutex_t		**forks;
	t_pdata				*brains;
	int					death;

	if (chk_args(ac, ag) == -1 || read_args(ag, 1) == 0)
		return (0);
	death = read_args(ag, 1);
	philos = (pthread_t *)malloc(sizeof(pthread_t) * death);
	brains = (t_pdata *)malloc(sizeof(t_pdata) * (death + 1));
	brains->meals = 0;
	brains->full = -1;
	if (ac == 6)
		brains->full = read_args(ag, 5);
	printf("death[%d]\n", death);
	brains->eat_dur = read_args(ag, 3);
	brains->slp_dur = read_args(ag, 4);
	brains->starve = read_args(ag, 2);
	brains->log = init_log();
	brains->death = &death;
	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * (death + 1));
	ac = -1;
	while (++ac <= death && printf("mutex malloc %d of %d\n", ac, death))
		forks[ac] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	brains->log_mtx = forks[0];
	death = 0;
	printf("commencing\n");
	commence_philosophy(read_args(ag, 1), philos, forks, brains);
	while (death == 0)
		if (brains->log->next != NULL)
			print_log(brains->log, brains->log_mtx);
	return (ac);
}
