/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:52:16 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/21 11:40:09 by rleskine         ###   ########.fr       */
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
	(brains + i)->sated = brains->sated;
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

	if (lock && brain->name % 2 == 1)
	{
		lock = pthread_mutex_lock(brain->left);
		if (lock)
			printf("Philo %d left fork: Error code %d when locking mutex\n", brain->name, lock);
		//printf("%9dms: Philo %2d picked up left fork\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name);
		//add_log_msg(brain, " picked up the left fork\n", NULL);
		lock = pthread_mutex_lock(brain->right);
		if (lock)
			printf("Error code %d when locking mutex\n", lock);
		//printf("%9dms: Philo %2d picked up right fork\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name);
		add_log_msg(brain, " picked up the forks\n", NULL, 0);
	}
	else if (lock)
	{
		lock = pthread_mutex_lock(brain->right);
		if (lock)
			printf("Error code %d when locking mutex\n", lock);
		//printf("%9dms: Philo %2d picked up right fork\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name);
		//add_log_msg(brain, " picked up the right fork\n", NULL);
		lock = pthread_mutex_lock(brain->left);
		if (lock)
			printf("Error code %d when locking mutex\n", lock);
		//printf("%9dms: Philo %2d picked up left fork\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name);
		add_log_msg(brain, " picked up the forks\n", NULL, 0);
	}
	else if (brain->name % 2 == 1)
	{
		pthread_mutex_unlock(brain->left);
		pthread_mutex_unlock(brain->right);
		add_log_msg(brain, " put down the forks\n", NULL, 0);
	}
	else
	{
		pthread_mutex_unlock(brain->left);
		pthread_mutex_unlock(brain->right);
		add_log_msg(brain, " put down the forks\n", NULL, 0);
	}
}

// void	manage_forks(t_pdata *brain, int lock)
// {
// 	pthread_mutex_t	*forks[2];

// 	//if ((brain->name % 2 == 1 && brain->meals % 2 == 0) || (brain->name % 2 == 0 && brain->meals == 1))
// 	if (brain->name % 2 == 0)
// 	{
// 		forks[0] = brain->left;
// 		forks[1] = brain->right;
// 	}
// 	else
// 	{
// 		forks[1] = brain->left;
// 		forks[0] = brain->right;
// 	}
// 	if (lock)
// 	{
// 		pthread_mutex_lock(forks[0]);
// 		pthread_mutex_lock(forks[1]);
// 		add_log_msg(brain, " picked up the forks\n", NULL);
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(forks[0]);
// 		pthread_mutex_unlock(forks[1]);
// 		add_log_msg(brain, " put down the forks\n", NULL);
// 	}
// }

void	rsleep(int ms)
{
	struct timeval	tv[2];

	gettimeofday(&tv[0], NULL);
	if (ms > 4)
		usleep((ms - 5) * 1000);
	ms = ms * 10;
	while (get_ms_diff(&tv[0], &tv[1], 10) < ms)
		usleep(200);
}

int	read_args(char **ag, int n)
{
	int		i;
	int		j;
	int		value;

	value = 0;
	j = 0;
	i = 0;
	while (ag[n][i])
	{
		if (ag[n][i] < 48 || ag[n][i] > 57)
			return (-1);
		i++;
	}
	while (j < i)
		value = value * 10 + (ag[n][j++] - '0');
	return (value);
}
