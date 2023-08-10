/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:52:16 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/24 18:43:59 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pdata	*make_brain(int i, t_pdata *brains, pthread_mutex_t **forks, int last)
{
	memset((brains + i), 0, sizeof(t_pdata));
	(brains + i)->name = i;
	(brains + i)->left = forks[i];
	if (last)
		(brains + i)->right = forks[1];
	else
		(brains + i)->right = forks[i + 1];
	(brains + i)->eat_dur = brains->eat_dur;
	(brains + i)->slp_dur = brains->slp_dur;
	(brains + i)->starve = brains->starve;
	(brains + i)->full = brains->full;
	(brains + i)->death = brains->death;
	(brains + i)->log_mtx = forks[0];
	(brains + i)->log = brains->log;
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

void	rsleep(int ms)
{
	struct timeval	tv[2];

	gettimeofday(&tv[0], NULL);
	if (ms > 10)
		usleep((ms - 10) * 1000);
	ms = ms * 10;
	while (get_ms_diff(&tv[0], &tv[1], 10) < ms)
		usleep(500);
}

t_pdata	*philostart(t_pdata *b, void *arg)
{
	b = (t_pdata *)arg;
	gettimeofday(&(b->start), NULL);
	gettimeofday(&(b->lastmeal), NULL);
	return (b);
}
