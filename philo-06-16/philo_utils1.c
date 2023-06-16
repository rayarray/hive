/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:52:16 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/16 16:20:31 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pdata	*make_brain(int i, t_pdata *brains, pthread_mutex_t *forks, int last)
{
	memset((brains + i), 0, sizeof(t_pdata));
	(brains + i)->name = i;
	(brains + i)->left = forks + i;
	if (last)
		(brains + i)->right = forks + 1;
	else
		(brains + i)->right = forks + i + 1;
	(brains + i)->eat_dur = brains->eat_dur;
	(brains + i)->slp_dur = brains->slp_dur;
	(brains + i)->starve = brains->starve;
	(brains + i)->meals = brains->meals;
	(brains + i)->death = brains->death;
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
	if (lock && brain->name % 2 == 1)
	{
		pthread_mutex_lock(brain->left);
		printf("%9dms: Philo %2d picked up left fork\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name);
		pthread_mutex_lock(brain->right);
		printf("%9dms: Philo %2d picked up right fork\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name);
	}
	else if (lock)
	{
		pthread_mutex_lock(brain->right);
		printf("%9dms: Philo %2d picked up right fork\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name);
		pthread_mutex_lock(brain->left);
		printf("%9dms: Philo %2d picked up left fork\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name);
	}
	else
	{
		pthread_mutex_unlock(brain->left);
		//printf("Philo %d picked up right fork\n");
		pthread_mutex_unlock(brain->right);
		//printf("Philo %d picked up left fork\n");
	}
}

void	rsleep(int ms)
{
	struct timeval	tv[2];

	gettimeofday(&tv[0], NULL);
	usleep((ms - 2) * 1000);
	while (get_ms_diff(&tv[0], &tv[1], 10) < ms * 10)
		usleep(250);
}
