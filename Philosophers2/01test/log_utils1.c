/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:49:24 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/21 12:26:12 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_logmsg	*init_log(void)
{
	t_logmsg	*log;

	log = (t_logmsg *)malloc(sizeof(t_logmsg));
	if (log == NULL)
		return (NULL);
	log->msg[0] = 0;
	log->len = 0;
	log->next = NULL;
	return (log);
}

void	add_log(t_logmsg *log, char *s)
{
	int	i;

	while (log && log->next)
		log = log->next;
	log->next = (t_logmsg *)malloc(sizeof(t_logmsg));
	if (log == NULL)
		return ;
	log = log->next;
	i = 0;
	while (s[i])
	{
		log->msg[i] = s[i];
		i++;
	}
	log->msg[i] = 0;
	log->len = i + 1;
	log->next = NULL;
}

int	nbr2str(int len, int nbr, char *s)
{
	int	i;
	int	dgts;

	i = nbr;
	dgts = 0;
	while (i > 0)
	{
		dgts++;
		i = i / 10;
	}
	if (dgts == 0)
	dgts = 1;
	i = len;
	while (i-- > dgts)
		*(s++) = ' ';
	if (dgts > len)
		len = dgts;
	while (dgts-- > 0)
	{
		i = (nbr / ya_power(10, dgts));
		*(s++) = '0' + i;
		nbr -= i * ya_power(10, dgts);
	}
	return (len);
}

void	log_msg(t_pdata *brain, char *s1, char *s2)
{
	char	*c;
	char	*s;
	int		ms;

	ms = get_ms_diff(&brain->start, &brain->now, 1);
	s = brain->msg;
	nbr2str(9, ms, s);
	s = s + 9;
	c = " ms: Philo ";
	while (*c)
		*(s++) = *(c++);
	ms = nbr2str(2, brain->name, s);
	s = s + ms;
	while (*s1)
		*(s++) = *(s1++);
	if (s2 && *s2)
	{
		ms = nbr2str(2, brain->meals, s);
		s = s + ms;
		while (*s2)
			*(s++) = *(s2++);
	}
	*s = 0;
}

void	add_log_msg(t_pdata *brain, char *s1, char *s2, int act)
{
	if (act == 1)
		(brain->meals)++;
	else if (act == 2)
		usleep(300);
	log_msg(brain, s1, s2);
	pthread_mutex_lock(brain->log_mtx);
	add_log(brain->log, brain->msg);
	if (act == 2)
	{
		(*(brain->sated))++;
		//printf("sated! s%d meals%d full%d", *brain->sated, brain->meals, brain->full);
	}
	pthread_mutex_unlock(brain->log_mtx);

}

