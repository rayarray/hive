/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:52:35 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/19 13:16:30 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_logmsg *log, pthread_mutex_t *mtx)
{
	t_logmsg	*prev;

	if (log && log->next)
	{
		prev = log;
		log = log->next;
		pthread_mutex_lock(mtx);
		prev->next = NULL;
	}
	else
		return ;
	while (log)
	{
		write (1, log->msg, log->len);
		prev = log;
		log = log->next;
		free(prev);
	}
	pthread_mutex_unlock(mtx);
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