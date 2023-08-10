/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:52:35 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/24 12:31:47 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_logmsg *msg, char *init)
{
	static char	s[40];
	static char	*p;
	static int	len;

	p = s;
	len = nbr2str(6, msg->timestamp, p) + 1;
	p[len - 1] = ' ';
	len = len + nbr2str(2, msg->philo, p + len);
	p += len;
	while (*init)
	{
		*p = *init;
		p++;
		init++;
		len++;
	}
	write(1, s, len);
}

void	choose_msg(t_logmsg *msg)
{
	if (msg->type == 0)
		print_msg(msg, " is thinking\n");
	else if (msg->type == 1)
		print_msg(msg, " is eating\n");
	else if (msg->type == 2)
		print_msg(msg, " is sleeping\n");
	else if (msg->type == 3)
		print_msg(msg, " is SATED\n");
	else if (msg->type == 4)
		print_msg(msg, " is DEAD\n");
	else if (msg->type == 5)
		print_msg(msg, " has taken a fork\n");
}

int	print_log(t_log *log, pthread_mutex_t *mtx)
{
	if (log->lines == 0 || log->lines == LOGSIZE)
		return (1);
	pthread_mutex_lock(mtx);
	log->lines2 = log->lines;
	log->i = log->l;
	log->l = log->l2;
	log->l2 = log->i;
	log->i = 0;
	log->lines = 0;
	pthread_mutex_unlock(mtx);
	while (log->i < log->lines2)
	{
		choose_msg(log->log + log->i + log->l2);
		if ((log->log + log->i + log->l2)->type == PHILO_SATED)
			(log->sated)--;
		if ((log->log + log->i + log->l2)->type == PHILO_DEAD
			|| log->sated == 0)
			break ;
		(log->i)++;
	}
	if ((log->log + log->i + log->l2)->type == PHILO_DEAD || log->sated == 0)
		log->i = 0;
	else
		log->i = 1;
	return (log->i);
}
