/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:53:29 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/22 10:56:03 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
