/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:49:24 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/22 10:46:40 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_log	*init_log(int philo)
{
	t_log	*log;

	log = (t_log *)malloc(sizeof(t_log));
	if (log == NULL)
		return (NULL);
	log->lines = 0;
	log->sated = philo;
	print_msg(NULL, "          ms: Philo ");
	return (log);
}

void	add_log(t_pdata *b, int type, int meal)
{
	if (b->log->lines >= LOGSIZE)
	{
		printf("LOG IS FULL!!\n");
		return ;
	}
	((b->log->log) + b->log->lines)->timestamp = get_ms_diff
		(&b->start, &b->now, 1);
	((b->log->log) + b->log->lines)->philo = b->name;
	((b->log->log) + b->log->lines)->type = type;
	((b->log->log) + b->log->lines)->meal = meal;
	(b->log->lines)++;
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

void	log_msg(t_pdata *b, int type, int meal)
{
	b->msg->type = type;
	b->msg->timestamp = get_ms_diff(&b->start, &b->now, 1);
	b->msg->meal = meal;
	b->msg->philo = b->name;
}

void	add_log_msg(t_pdata *b, int type, int meal)
{
	pthread_mutex_lock(b->log_mtx);
	add_log(b, type, meal);
	pthread_mutex_unlock(b->log_mtx);
}
