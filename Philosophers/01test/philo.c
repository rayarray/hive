/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:30:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/21 12:35:48 by rleskine         ###   ########.fr       */
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

void	*logger(void *arg)
{
	t_pdata	*b;

	b = arg;
	while (*b->death == 0 && *b->sated < b->name)
	{
		usleep(500);
		if (b->log->next != NULL)
			print_log(b->log, b->log_mtx);
	}
	usleep(2000);
	print_log(b->log, b->log_mtx);
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
		add_log_msg(brain, " started thinking\n", NULL, 0);
		manage_forks(brain, 1);
		if (get_ms_diff(&brain->lastmeal, &brain->now, 1) > brain->starve)
		{
			add_log_msg(brain, " DIED\n", NULL, 0);
			*(brain->death) = brain->name;
			//manage_forks(brain, 0);
			pthread_exit(NULL);
		}
		gettimeofday(&(brain->lastmeal), NULL);
		add_log_msg(brain, " started eating the ", "th meal\n", 1);
		rsleep(brain->eat_dur);
		manage_forks(brain, 0);
		if (brain->meals == brain->full)
			break ;
		add_log_msg(brain, " started sleeping\n", NULL, 0);
		rsleep(brain->slp_dur);
	}
	if (brain->meals == brain->full)
		add_log_msg(brain, " is sated\n", NULL, 2);
	//add_log_msg(brain, " exited\n", NULL, 0);
	pthread_exit(NULL);
}

int	commence_philosophy(int size, pthread_t *philos, pthread_mutex_t **forks,
	t_pdata *brains)
{
	int					result;
	int					i;

	i = -1;
	while (++i <= size)
	{
		//printf("mtxinit%d size:%d\n", i, size);
		result = pthread_mutex_init(forks[i], NULL);
		if (result)
			printf("Mutex creation error %d\n", result);
	}
	usleep(2500);
	i = 0;
	while (++i < size)
	{
		//printf("mkb %d\n", i);
		make_brain(i, brains, forks, 0);
	}
	make_brain(i, brains, forks, 1);
	i = -1;
	while (++i <= size)
	{
		//printf("create philos [%d]\n", i);
		if (i == 0)
			result = pthread_create(&philos[0], NULL, logger, brains);
		else
			result = pthread_create(&philos[i], NULL, philosopher, brains + i);
		if (result)
			printf("Thread creation failed\n");
		result = pthread_detach(philos[i]);
		if (result)
			printf("Thread detach failed\n");
	}
	while (--i >= 0)
	{
		result = pthread_join(philos[i], NULL);
		while (result && result != 3)
		{
			usleep(2000);
			result = pthread_join(philos[i], NULL);
			//if (result)
			//	printf("Thread join failed %d\n", result);
		}
		//	perror("Thread join failed");
	}
	return (1);
}

int	main(int ac, char **ag)
{
	t_table				t;

	if (chk_args(ac, ag) == -1 || read_args(ag, 1) == 0)
		return (0);
	memset(&t, 0, sizeof(t_table));
	t.philo = read_args(ag, 1);
	t.philos = (pthread_t *)malloc(sizeof(pthread_t) * (t.philo + 1));
	t.brains = (t_pdata *)malloc(sizeof(t_pdata) * (t.philo + 1));
	t.brains->meals = 0;
	t.brains->full = -1;
	if (ac == 6)
		t.brains->full = read_args(ag, 5);
	//printf("t.philo[%d]\n", t.philo);
	t.brains->eat_dur = read_args(ag, 3);
	t.brains->slp_dur = read_args(ag, 4);
	t.brains->starve = read_args(ag, 2);
	t.brains->log = init_log();
	t.brains->name = t.philo;
	t.brains->death = &t.death;
	t.brains->sated = &t.sated;
	t.forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * (t.philo + 1));
	ac = -1;
	while (++ac <= t.philo && printf("mutex malloc %d of %d\n", ac, t.philo))
		t.forks[ac] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	t.brains->log_mtx = t.forks[0];
	//printf("commencing\n");
	commence_philosophy(read_args(ag, 1), t.philos, t.forks, t.brains);
	// while (t.death == 0 && t.sated < t.philo)
	// 	if (t.brains->log->next != NULL)
	// 		print_log(t.brains->log, t.brains->log_mtx);
	//printf("ac%d\n", ac);
	// int	result;
	// while (--ac >= 0)
	// {
	// 	printf("joining thread %d\n", ac);
	// 	result = pthread_join(*(t.philos), NULL);
	// 	if (result)
	// 		printf("join failed with error %d\n", result);
	// }
	while (t.death == 0 && t.sated < t.philo)
		usleep(1000);
	usleep(2000);
	//pthread_exit(0);
	return (ac);
}
