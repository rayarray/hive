/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:49:24 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/10 11:15:19 by rleskine         ###   ########.fr       */
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
	log->l = 0;
	log->l2 = LOGSIZE;
	log->sated = philo;
	return (log);
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
