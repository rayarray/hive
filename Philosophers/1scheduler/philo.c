/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:30:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/10 10:43:22 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *arg)
{
	t_pdata			*brain;
	struct timeval	lastmeal;
	struct timeval	timer;
	struct timeval	now;

	brain = (t_pdata *)arg;
	while (brain->launch != NULL)
		usleep(500);
	while (*(brain->death) == 0 && brain->log->sated > 0)
	{
		set_timer(&brain->lastmeal, &lastmeal, 0);
		set_timer(&lastmeal, &timer, brain->starve);
		// wait_timer(&timer, &now);
		// if (lastmeal.tv_sec == brain->lastmeal.tv_sec && lastmeal.tv_usec
		// 	== brain->lastmeal.tv_usec && *(brain->death) == 0
		// 	&& brain->log->sated > 0 && chk_timer(&timer, &now))
		// 	add_log_msg(brain, PHILO_DEAD, 0);
		while (lastmeal.tv_sec == brain->lastmeal.tv_sec && lastmeal.tv_usec
			== brain->lastmeal.tv_usec && *(brain->death) == 0 && brain->log->sated > 0)
		{
			if (!chk_timer(&timer, &now))
				usleep(2500);
			else if (*(brain->death) == 0 && brain->log->sated > 0)
				add_log_msg(brain, PHILO_DEAD, 0);
		}
	}
	pthread_exit(NULL);
}

void	*philosopher(void *arg)
{
	t_pdata			*brain;
	struct timeval	eatslp[2];

	brain = (t_pdata *)arg;
	brain = philostart(NULL, arg);
	set_timer(&(brain->lastmeal), &eatslp[0], brain->wait);
	wait_timer(&eatslp[0], &(brain->lastmeal));
	while (*(brain->death) == 0)
	{
		add_log_msg(brain, PHILO_THINKING, 0);
		manage_forks(brain, 1);
		gettimeofday(&(brain->lastmeal), NULL);
		set_timer(&(brain->lastmeal), &eatslp[0], brain->eat_dur);
		add_log_msg(brain, PHILO_EATING, ++(brain->meals));
		wait_timer(&eatslp[0], &eatslp[1]);
		manage_forks(brain, 0);
		if (brain->meals == brain->full)
			break ;
		set_timer(&eatslp[0], &eatslp[1], brain->slp_dur); // +
		//	(brain->starve - brain->eat_dur + brain->slp_dur) / 2);
		add_log_msg(brain, PHILO_SLEEPING, 0);
		wait_timer(&eatslp[1], &eatslp[0]);
		//usleep(10 * brain->eat_dur / brain->wait);
	}
	if (brain->meals == brain->full)
		add_log_msg(brain, PHILO_SATED, 0);
	pthread_exit(NULL);
}

int	commence_philosophy(t_table *t)
{
	int	result;
	int	i;

	i = -1;
	while (++i <= t->philos + 1)
	{
		result = pthread_mutex_init((t->f)[i], NULL);
		if (result)
			printf("Mutex creation error %d\n", result);
	}
	i = 0;
	while (++i <= t->philos)
		make_brain(i, t->b, t->f, t->philos);
	while (--i >= 0)
		(t->b + i)->super = t->sv + i - 1;
	while (++i < t->philos)
	{
		result = pthread_create(t->p + i, NULL, philosopher, t->b + i + 1);
		if (result)
			printf("Thread creation failed\n");
		//result = pthread_detach(*(t->p + i));
		//if (result)
		//	printf("Thread detach failed\n");
	}
	return (1);
}

int	init_table(t_table *t, char **ag, int ac, int i)
{
	t->philos = read_args(ag, 1);
	t->p = (pthread_t *)malloc(sizeof(pthread_t) * (t->philos));
	t->sv = (pthread_t *)malloc(sizeof(pthread_t) * (t->philos));
	t->b = (t_pdata *)malloc(sizeof(t_pdata) * (t->philos + 1));
	t->f = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
			* (t->philos + 2));
	if (t->p == NULL || t->sv == NULL || t->b == NULL || t->f == NULL)
		return (0);
	t->i = t->philos;
	while (++i <= t->philos + 1)
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
	//t->b->wait = t->b->starve - (t->b->eat_dur + t->b->slp_dur);
	return (1);
}

int	main(int ac, char **ag)
{
	t_table	t;

	if (chk_args(ac, ag) == -1 || read_args(ag, 1) == 0)
		return (0);
	if (init_table(&t, ag, ac, -1) == 1)
	{
		commence_philosophy(&t);
		while (print_log(t.b->log, *(t.f)))
			usleep(1000);
	}
	while (t.i-- > 0)
		pthread_join(*(t.sv + t.i), NULL);
	t.i = t.philos;
	while (t.i-- > 0)
		pthread_join(*(t.p + t.i), NULL);
	if (t.p != NULL)
		free (t.p);
	if (t.sv != NULL)
		free (t.sv);
	if (t.b->log != NULL)
		free (t.b->log);
	if (t.b != NULL)
		free (t.b);
	ac = -1;
	while (t.f && ++ac <= t.philos + 1 && t.f[ac] != NULL)
		pthread_mutex_destroy(t.f[ac]);
	ac = -1;
	while (t.f && ++ac <= t.philos + 1 && t.f[ac] != NULL)
		free(t.f[ac]);
	if (t.f != NULL)
		free (t.f);
	return (0);
}
