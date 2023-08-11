/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:37:57 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/11 16:59:10 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timernode	*make_timernode(t_table *t)
{
	t_timernode	*n;

	n = (t_timernode *)malloc(sizeof(t_timernode));
	if (n == NULL)
		return (NULL);
	n->id = 0;
	if (pthread_mutex_init(&n->lock, NULL))
		printf("Mutex creation error\n");
	n->timers = &t->timers;
	n->schedule = &t->schedule;
	n->next = NULL;
	return (n);
}

void	add_timer(t_timernode *n, t_timernode *s, t_timernode *t)
{
	t_timernode	*i;

	pthread_mutex_lock(&t->lock);
	*(n->timers) = t->next;
	n->id = ++(t->id);
	n->next = t;
	t->time.tv_sec = n->time.tv_sec;
	t->time.tv_usec = n->time.tv_usec;
	if (s == NULL)
		*(n->schedule) = t;
	else if (s->time.tv_sec < n->time.tv_sec || (s->time.tv_sec
		== n->time.tv_sec && s->time.tv_usec > n->time.tv_usec))
	{
		t->next = s;
		*(n->schedule) = t;
	}
	while (s && s->next && (s->time.tv_sec < n->time.tv_sec
		|| (s->time.tv_sec == n->time.tv_sec && s->time.tv_usec <
		n->time.tv_sec)))
		s = s->next;
	
	

}

void	schedule_timer(t_timernode *n, struct timeval *t, int ms)
{
	n->time.tv_sec = t->tv_sec;
	n->time.tv_usec = t->tv_usec + (ms * 1000);
	while (n->time.tv_usec > 999999)
	{
		n->time.tv_usec -= 1000000;
		(n->time.tv_sec)++;
	}
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
	add_timer(n, *(n->schedule), *(n->timers));
	pthread_mutex_unlock(n->timerlock);
}

void	start_scheduler(t_table *t)
{
	t_timernode	*n;

	t->timers = make_timernode(t, NULL);
	if (t->timers == NULL)
		return ;
	n = t->timers;
	t->i = 1;
	while (t->i < t->philos)
	{
		n->next = make_timernode(t, NULL);
		if (n->next == NULL)
			return ;
		n = n->next;
	}
	
}