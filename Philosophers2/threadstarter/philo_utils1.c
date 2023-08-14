/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:52:16 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/14 15:48:15 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pdata	*make_brain(int i, t_pdata *brains, pthread_mutex_t *slp, int last)
{
	memset((brains + i), 0, sizeof(t_pdata));
	(brains + i)->name = i;
	(brains + i)->slp = slp;
	(void)last;
	// (brains + i)->left = forks[i + 1];
	// if (i == last)
	// 	(brains + i)->right = forks[2];
	// else
	// 	(brains + i)->right = forks[i + 2];
	// (brains + i)->eat_dur = brains->eat_dur;
	// (brains + i)->slp_dur = brains->slp_dur;
	// (brains + i)->starve = brains->starve;
	// (brains + i)->full = brains->full;
	// (brains + i)->death = brains->death;
	// (brains + i)->log_mtx = forks[0];
	// (brains + i)->launch = forks[1];
	// (brains + i)->log = brains->log;
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

