/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:31:20 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/16 15:07:23 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_pdata {
	int					name;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	struct timeval		start;
	struct timeval		lastmeal;
	struct timeval		now;
	int					meals;
	int					full;
	int					*death;
	void				*print;
	int					eat_dur;
	int					slp_dur;
	int					starve;
}	t_pdata;

// philo_utils1.c

t_pdata	*make_brain(int i, t_pdata *brains, pthread_mutex_t *forks, int last);
int		get_ms_diff(struct timeval *t1, struct timeval *t2, int now);
void	manage_forks(t_pdata *brain, int lock);
void	rsleep(int ms);

#endif	/* PHILO_H */