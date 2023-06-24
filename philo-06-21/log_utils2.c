/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:52:35 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/21 15:06:58 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_logmsg *msg, char *init)
{
	static char	s[80];
	static char	*p;
	static int	len;

	if (msg == NULL && init)
	{
		len = 0;
		while (init[len] && ++len)
			s[len - 1] = init[len - 1];
		return ;
	}
	p = s;
	len = 11 + nbr2str(9, msg->timestamp, p);
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
		print_msg(msg, " picked up the forks\n");
	else if (msg->type == 6)
		print_msg(msg, " put down the forks\n");
}

int	print_log(t_log *log, pthread_mutex_t *mtx)
{
	int	i;

	if (log->lines == 0)
		return (1);
	i = 0;
	pthread_mutex_lock(mtx);
	while (i < log->lines)
	{
		choose_msg(log->log + i);
		if ((log->log + i)->type == PHILO_SATED)
			(log->sated)--;
		if ((log->log + i)->type == PHILO_DEAD || log->sated == 0)
		{
			printf("dead%d sated%d", (log->log + i)->type, log->sated);
			break ;
		}
		i++;
	}
	log->lines = 0;
	if ((log->log + i)->type == PHILO_DEAD || log->sated == 0)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(mtx);
	return (i);
}

int	ya_power(int nbr, int pow)
{
	int	i;

	i = nbr;
	if (pow == 0)
		return (1);
	while (pow-- > 1)
		i = i * nbr;
	return (i);
}