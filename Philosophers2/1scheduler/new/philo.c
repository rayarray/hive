/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:11:38 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/14 13:03:46 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_pdata	*b;

	b = philostart(NULL, arg);
	while (*(b->death) == 0)
	{
		add_log_msg(b, PHILO_THINKING, 0);
		manage_forks(b, 1);
		gettimeofday(&(b->lastmeal), NULL);
		b->timer = schedule_timer(NULL, &(b->lastmeal), b->eat_dur);
		add_log_msg(b, PHILO_EATING, ++(b->meals));
		pthread_mutex_lock(b->timer);
		pthread_mutex_unlock(b->timer);
		manage_forks(b, 0);
		gettimeofday(&(b->now), NULL);
		if (b->meals == b->full)
			break ;
		schedule_timer(NULL, &(b->now), b->slp_dur);
		add_log_msg(b, PHILO_SLEEPING, 0);
		pthread_mutex_lock(b->timer);
		pthread_mutex_unlock(b->timer);
	}
	if (b->meals == b->full)
		add_log_msg(b, PHILO_SATED, 0);
	pthread_exit(NULL);
}

int	commence_philosophy(t_table *t, int i)
{
	while (++i < t->philos)
		if (pthread_mutex_init(t->forks + i, NULL))
			printf("Mutex creation error\n");
	i = t->philos;
	while (--i < t->philos)
		make_brain(i, t->b, t->forks, t->philos);
	if (pthread_create(&(t->sv), NULL, supervisor, t)
		|| pthread_create(&(t->schd), NULL, scheduler, t))
		printf("Thread creation failed");
	while (++i < t->philos)
		if (pthread_create(t->p + i, NULL))
			printf("Thread creation failed");
	return (1);
}

int	init_table(t_table *t, char **ag, int ac, int i)
{
	t->philos = read_args(ag, 1);
	t->p = (pthread_t *)malloc(sizeof(pthread_t) * (t->philos));
	t->b = (t_pdata *)malloc(sizeof(t_pdata) * (t->philos));
	t->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (t->philos + 2));
	t->schd_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (t->philos));
	if (t->p == NULL || t->b == NULL || t->forks == NULL || t->schd_m == NULL)
		return (0);
	t->b->full = -1;
	if (ac == 6)
		t->b->full = read_args(ag, 5);
	t->b->eat_dur = read_args(ag, 3);
	t->b->slp_dur = read_args(ag, 4);
	t->b->starve = read_args(ag, 2);
	t->b->log = init_log(t->philos);
	t->b->timer = make_timernode(t);
	if (t->b->log == NULL)
		return (0);
	t->b->death = &t->death;
	t->b->log_mtx = &t->log;
	t->death = 0;
	return (1);
}

int	main(int ac, char **ag)
{
	t_table	t;

	if (chk_args(ac, ag) == -1 || read_args(ag, 1) == 0)
		return (0);
	if (init_table(&t, ag, ac, -1) == 1)
	{
		//start_scheduler(t);
		commence_philosophy(&t, -1);
		while (print_log(t.b->log, &t.log))
			usleep(250);
	}
	t.i = t.philos;
	while (--t.i >= 0)
		pthread_join(*(t.p + t.i), NULL);
	pthread_join(t.sv, NULL);
	pthread_join(t.schd, NULL);
	ac = -1;
	while (t.forks && ++ac <= t.philos, &t.forks[ac] != NULL)
		pthread_mutex_destroy(&t.forks[ac]);
	ac = -1;
	while (t.forks && ++ac <= t.philos, &t.forks[ac] != NULL)
		free(t.forks[ac]);
	if (t.forks != NULL)
		free (t.forks);
}
