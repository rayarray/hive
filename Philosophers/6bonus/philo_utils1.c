/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:52:16 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/05 18:43:58 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_pdata	*make_brain(int i, t_pdata *brains, pthread_mutex_t **forks, int last)
{
	memset((brains + i), 0, sizeof(t_pdata));
	(brains + i)->name = i;
	(brains + i)->left = forks[i + 1];
	if (last)
		(brains + i)->right = forks[2];
	else
		(brains + i)->right = forks[i + 2];
	(brains + i)->eat_dur = brains->eat_dur;
	(brains + i)->slp_dur = brains->slp_dur;
	(brains + i)->starve = brains->starve;
	(brains + i)->full = brains->full;
	(brains + i)->death = brains->death;
	(brains + i)->log_mtx = forks[0];
	(brains + i)->launch = forks[1];
	(brains + i)->log = brains->log;
	//if (brains->wait >= 0)
	//	(brains + i)->wait = brains->wait / 2;
	//else
	(brains + i)->wait = 0;
	return (brains + i);
}

int	get_ms_diff(struct timeval *t1, struct timeval *t2, int now)
{
	if (now)
		gettimeofday(t2, NULL);
	if (now == 10)
	{
		now = (t2->tv_sec - t1->tv_sec) * 10000;
		now += (t2->tv_usec - t1->tv_usec) / 100;
		return (now);
	}
	now = (t2->tv_sec - t1->tv_sec) * 1000;
	now += (t2->tv_usec - t1->tv_usec) / 1000;
	return (now);
}

void	manage_forks(t_pdata *brain, int lock)
{
	if (lock)
	{
		if (brain->name % 2 == 0)
			lock = pthread_mutex_lock(brain->left);
		else
			lock = pthread_mutex_lock(brain->right);
		if (lock)
			printf("P%d: Error code %d when locking mutex\n", brain->name, lock);
		add_log_msg(brain, PHILO_UPFORK, 0);
		if (brain->name % 2 == 0)
			lock = pthread_mutex_lock(brain->right);
		else
			lock = pthread_mutex_lock(brain->left);
		if (lock)
			printf("P%d: Error code %d when locking mutex\n", brain->name, lock);
		add_log_msg(brain, PHILO_UPFORK, 0);
		return ;
	}
	if (brain->name % 2 == 0)
		pthread_mutex_unlock(brain->left);
	pthread_mutex_unlock(brain->right);
	if (brain->name % 2 == 1)
		pthread_mutex_unlock(brain->left);
}

int	init_table(t_table *t, char **ag, int ac, int i)
{
	t->philos = read_args(ag, 1);
	t->p = (pthread_t *)malloc(sizeof(pthread_t) * (t->philos));
	t->sv = (pthread_t *)malloc(sizeof(pthread_t) * (t->philos));
	t->b = (t_pdata *)malloc(sizeof(t_pdata) * (t->philos + 1));
	sem_init(t->forks, 0, t->philos);
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
	t->b->wait = t->b->starve - (t->b->eat_dur + t->b->slp_dur);
	return (1);
}

t_pdata	*philostart(t_pdata *b, void *arg)
{
	b = (t_pdata *)arg;
	pthread_mutex_lock(b->launch);
	pthread_create(b->super, NULL, supervisor, b);
	pthread_mutex_unlock(b->launch);
	gettimeofday(&(b->start), NULL);
	gettimeofday(&(b->lastmeal), NULL);
	//printf("start s[%ld]u[%d] lastmeal s[%ld]u[%d]\n", b->start.tv_sec, 
	//	b->start.tv_usec, b->lastmeal.tv_sec, b->lastmeal.tv_usec);
	b->launch = NULL;
	return (b);
}
