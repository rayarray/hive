/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:37:57 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/14 15:10:25 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>

t_timernode	*make_timernode(t_table *t)
{
	t_timernode	*n;

	n = (t_timernode *)malloc(sizeof(t_timernode));
	if (n == NULL)
		return (NULL);
	n->id = 0;
	if (pthread_mutex_init(&n->lock, NULL))
		printf("Mutex creation error\n");
	n->timerlock = &t->schd_lock;
	n->timerfull = &t->schd_full;
	n->timers = &t->timers;
	n->schedule = &t->schedule;
	n->next = NULL;
	return (n);
}

void	add_timer(t_timernode *n, t_timernode *s, t_timernode *t)
{
	pthread_mutex_lock(&n->lock);
	*(n->timers) = t->next;
	n->id++;
	if (s == NULL)
		*(n->schedule) = t;
	else if (s->time.tv_sec < n->time.tv_sec || (s->time.tv_sec
			== n->time.tv_sec && s->time.tv_usec > n->time.tv_usec))
	{
		t->next = s;
		*(n->schedule) = t;
	}
	while (s && s->next && (s->next->time.tv_sec < n->time.tv_sec
			|| (s->next->time.tv_sec == n->time.tv_sec
				&& s->next->time.tv_usec < n->time.tv_sec)))
		s = s->next;
	t->next = s->next;
	s->next = t;
}

pthread_mutex_t	*schedule_timer(t_timernode *n, struct timeval *t, int ms)
{
	pthread_mutex_lock(n->timerlock);
	if (*(n->timers) == NULL)
	{
		pthread_mutex_unlock(n->timerlock);
		pthread_mutex_lock(n->timerfull);
		while (*(n->timers) == NULL)
			;
		pthread_mutex_lock(n->timerlock);
		pthread_mutex_unlock(n->timerfull);
	}
	n = *(n->timers);
	n->time.tv_sec = t->tv_sec;
	n->time.tv_usec = t->tv_usec + (ms * 1000);
	while (n->time.tv_usec > 999999)
	{
		n->time.tv_usec -= 1000000;
		(n->time.tv_sec)++;
	}
	add_timer(n, *(n->schedule), *(n->timers));
	pthread_mutex_unlock(n->timerlock);
	return (&n->lock);
}

void	start_scheduler(t_table *t)
{
	t_timernode	*n;

	if (pthread_mutex_init(&t->schd_lock, NULL))
		printf("Mutex creation error\n");
	if (pthread_mutex_init(&t->schd_full, NULL))
	t->timers = make_timernode(t, NULL);
	if (t->timers == NULL)
		return ;
	n = t->timers;
	t->i = 0;
	while (++(t->i) < t->philos)
	{
		n->next = make_timernode(t, NULL);
		if (n->next == NULL)
			return ;
		n = n->next;
	}
}

void	scheduler(void *arg)
{
	t_table			*t;
	struct timeval	now;
	t_timernode		*n[2];

	t = (t_table *)arg;
	while (t->death == 0)
	{
		pthread_mutex_lock(&t->schd_lock);
		gettimeofday(now, NULL);
		n[0] = t->schedule;
		n[1] = t->schedule;
		while (n[1] && ((n[1]->time.tv_usec < now.tv_sec)
				|| (n[1]->time.tv_sec == now.tv_sec && n[1]->time.tv_usec
					<= now.tv_usec)))
				n[1] = n[1]->next;
		t->schedule = n[1]->next;
		n[1]->next = NULL;
		n[1] = n[0];
		while (n[0])
		{
			pthread_mutex_unlock(&n[0]->lock);
			n[0] = n[0]->next;
		}
		
	}
}
