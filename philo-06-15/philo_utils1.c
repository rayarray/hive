/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:52:16 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/15 16:37:26 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pdata	*make_brain(int i, t_pdata *brains, pthread_mutex_t *forks, int last)
{
	memset((brains + i), 0, sizeof(t_pdata));
	(brains + i)->name = (i + 1);
	(brains + i)->left = forks + i;
	if (last)
		(brains + i)->right = forks + 1;
	else
		(brains + i)->right = forks + i + 1;
	(brains + i)->eat_dur = brains->eat_dur;
	(brains + i)->slp_dur = brains->slp_dur;
	(brains + i)->meals = brains->meals;
	(brains + i)->death = brains->death;
	return (brains + i);
}