/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:31:20 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/15 16:37:27 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>	// FOR PRINTF, REMOVE!

typedef struct s_pdata {
	int					name;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	struct timeval		lastmeal;
	int					meals;
	int					full;
	int					*death;
	void				*print;
	int					eat_dur;
	int					slp_dur;
}	t_pdata;

// philo_utils1.c

t_pdata	*make_brain(int i, t_pdata *brains, pthread_mutex_t *forks, int last);

#endif	/* PHILO_H */