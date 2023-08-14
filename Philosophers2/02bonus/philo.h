/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:31:20 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/19 17:39:16 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_logmsg {
	char	msg[80];
	int		len;
	void	*next;
}	t_logmsg;

typedef struct s_pdata {
	int					name;
	//pthread_mutex_t		*left;
	//pthread_mutex_t		*right;
	//sem_t				*forks;
	struct timeval		start;
	struct timeval		lastmeal;
	struct timeval		now;
	int					meals;
	int					full;
	int					*death;
	pthread_mutex_t		*log_mtx;
	t_logmsg			*log;
	char				msg[80];
	int					eat_dur;
	int					slp_dur;
	int					starve;
}	t_pdata;

// philo_utils1.c

t_pdata		*make_brain(int i, t_pdata *brains, sem_t *forks, int last);
int			get_ms_diff(struct timeval *t1, struct timeval *t2, int now);
void		manage_forks(t_pdata *brain, int lock);
void		rsleep(int ms);
int			read_args(char **ag, int n);

// log_utils1.c

t_logmsg	*init_log(void);
void		add_log(t_logmsg *log, char *s);
void		log_msg(t_pdata *brain, char *status, char *status2);
void		add_log_msg(t_pdata *brain, char *s1, char *s2);

// log_utils2.c

void		print_log(t_logmsg *log, pthread_mutex_t *mtx);
int			ya_power(int nbr, int pow);

#endif	/* PHILO_H */