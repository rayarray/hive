/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:30:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/22 10:57:29 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chk_args(int ac, char **ag)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: philos a b c d [e]\n\nWhere a is the number of philosop");
		printf("hers, b is the time they can survive between\nmeals (counted");
		printf(") from the start of the meal), c is the time it takes to eat\n");
		printf("and d is the time it takes to sleep. Optionally [e] can be s");
		printf("pecified as the\n");
		printf("number of meals each philosopher can eat before stopping\n");
		return (-1);
	}
	if (read_args(ag, 1) == -1 || read_args(ag, 2) == -1
		|| read_args(ag, 3) == -1 || read_args(ag, 4) == -1)
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

void	*philosopher(void *arg)
{
	t_pdata	*brain;

	brain = philostart(NULL, arg);
	while (*(brain->death) == 0)
	{
		add_log_msg(brain, PHILO_THINKING, 0);
		manage_forks(brain, 1);
		if (get_ms_diff(&brain->lastmeal, &brain->now, 1) > brain->starve)
		{
			add_log_msg(brain, PHILO_DEAD, 0);
			*(brain->death) = brain->name;
			pthread_exit(NULL);
		}
		gettimeofday(&(brain->lastmeal), NULL);
		add_log_msg(brain, PHILO_EATING, ++(brain->meals));
		rsleep(brain->eat_dur);
		manage_forks(brain, 0);
		if (brain->meals == brain->full)
			break ;
		add_log_msg(brain, PHILO_SLEEPING, 0);
		rsleep(brain->slp_dur);
	}
	if (brain->meals == brain->full)
		add_log_msg(brain, PHILO_SATED, 0);
	pthread_exit(NULL);
}

int	commence_philosophy(int size, pthread_t philos[], pthread_mutex_t **forks,
	t_pdata *brains)
{
	int	result;
	int	i;

	i = -1;
	while (++i <= size)
	{
		result = pthread_mutex_init(forks[i], NULL);
		if (result)
			printf("Mutex creation error %d\n", result);
	}
	usleep(5000);
	i = 0;
	while (++i <= size)
		make_brain(i, brains, forks, i / size);
	i = 0;
	while (++i <= size)
	{
		result = pthread_create(philos + i - 1, NULL, philosopher, brains + i);
		if (result)
			printf("Thread creation failed\n");
		result = pthread_detach(*(philos + i - 1));
		if (result)
			printf("Thread detach failed\n");
	}
	return (1);
}

int	init_table(t_table *t, char **ag, int ac, int i)
{
	t->philos = read_args(ag, 1);
	t->p = (pthread_t *)malloc(sizeof(pthread_t) * (t->philos));
	t->b = (t_pdata *)malloc(sizeof(t_pdata) * (t->philos + 1));
	t->f = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
			* (t->philos + 1));
	if (t->p == NULL || t->b == NULL || t->f == NULL)
		return (0);
	while (++i <= t->philos)
		t->f[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	t->b->full = -1;
	if (ac == 6)
		t->b->full = read_args(ag, 5);
	t->b->eat_dur = read_args(ag, 3);
	t->b->slp_dur = read_args(ag, 4);
	t->b->starve = read_args(ag, 2);
	t->b->log = init_log(t->philos);
	if (t->b->log == NULL)
		return (0);
	t->b->death = &t->death;
	t->b->log_mtx = t->f[0];
	t->death = 0;
	return (1);
}

int	main(int ac, char **ag)
{
	t_table				t;

	if (chk_args(ac, ag) == -1 || read_args(ag, 1) == 0)
		return (0);
	if (init_table(&t, ag, ac, -1) == 1)
	{
		commence_philosophy(t.philos, t.p, t.f, t.b);
		while (print_log(t.b->log, *t.f))
			usleep(500);
	}
	if (t.p != NULL)
		free (t.p);
	if (t.b->log != NULL)
		free (t.b->log);
	if (t.b != NULL)
		free (t.b);
	ac = -1;
	while (++ac <= t.philos && t.f[ac] != NULL)
		free(t.f[ac]);
	if (t.f != NULL)
		free (t.f);
	return (0);
}
