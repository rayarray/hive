/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:52:16 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/09 17:43:12 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pdata	*make_brain(int i, t_pdata *brains, pthread_mutex_t **forks, int last)
{
	memset((brains + i), 0, sizeof(t_pdata));
	(brains + i)->name = i;
	(brains + i)->left = forks[i + 1];
	if (i == last)
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
	// if (brains->wait >= 0)
	// 	(brains + i)->wait = brains->wait;
	// else
	// 	(brains + i)->wait = 0;
	if (last % 2 == 0 && i % 2 == 0)
		(brains + i)->wait = brains->eat_dur;
	else
		(brains + i)->wait = brains->eat_dur * ((i + 2) % 3);
	//printf("philo[%d]wait[%d]\n", i, (brains + i)->wait);
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
		if (1 || brain->name % 2 == 0)
			lock = pthread_mutex_lock(brain->left);
		else
			lock = pthread_mutex_lock(brain->right);
		if (lock)
			printf("P%d: Error code %d when locking mutex\n", brain->name, lock);
		add_log_msg(brain, PHILO_LFORK, 0);
		if (1 || brain->name % 2 == 0)
			lock = pthread_mutex_lock(brain->right);
		else
			lock = pthread_mutex_lock(brain->left);
		if (lock)
			printf("P%d: Error code %d when locking mutex\n", brain->name, lock);
		add_log_msg(brain, PHILO_RFORK, 0);
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

	//gettimeofday(&tv[0], NULL);
	set_timer(NULL, &tv[0], ms);
	if (ms > 10)
		usleep((ms - (ms / 8)) * 1000);
	//ms = ms * 10;
	//while (get_ms_diff(&tv[0], &tv[1], 10) < ms)
	while (!chk_timer(&tv[0], &tv[1]))
		usleep(500);
}

t_pdata	*philostart(t_pdata *b, void *arg)
{
	b = (t_pdata *)arg;
	pthread_mutex_lock(b->launch);
	pthread_create(b->super, NULL, supervisor, b);
	pthread_detach(*(b->super));
	pthread_mutex_unlock(b->launch);
	gettimeofday(&(b->start), NULL);
	gettimeofday(&(b->lastmeal), NULL);
	//printf("start s[%ld]u[%d] lastmeal s[%ld]u[%d]\n", b->start.tv_sec, b->start.tv_usec, b->lastmeal.tv_sec, b->lastmeal.tv_usec);
	b->launch = NULL;
	return (b);
}
