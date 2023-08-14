/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:31:20 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/10 14:51:08 by rleskine         ###   ########.fr       */
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

# define PHILO_THINKING	0
# define PHILO_EATING	1
# define PHILO_SLEEPING	2
# define PHILO_SATED	3
# define PHILO_DEAD		4
# define PHILO_UPFORK	5

# define LOGSIZE	2500

typedef struct s_logmsg {
	int		timestamp;
	int		philo;
	int		type;
	int		meal;
}	t_logmsg;

typedef struct s_log {
	t_logmsg	log[LOGSIZE * 2];
	int			lines;
	int			l;
	int			sated;
	int			lines2;
	int			l2;
	int			i;
}	t_log;

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
	pthread_mutex_t		*log_mtx;
	t_logmsg			*msg;
	t_log				*log;
	int					eat_dur;
	int					slp_dur;
	int					starve;
	int					wait;
}	t_pdata;

typedef struct s_table {
	int					philos;
	int					death;
	pthread_t			*p;
	pthread_mutex_t		**f;
	t_pdata				*b;
}	t_table;

// philo_utils1.c

t_pdata		*make_brain(int i, t_pdata *brains, pthread_mutex_t **forks,
				int last);
int			get_ms_diff(struct timeval *t1, struct timeval *t2, int now);
void		manage_forks(t_pdata *brain, int lock);
void		rsleep(int ms);
t_pdata		*philostart(t_pdata *b, void *arg);

// philo_utils2.c

int			read_args(char **ag, int n);

// log_utils1.c

t_log		*init_log(int philo);
void		add_log(t_pdata *b, int type, int meal);
int			nbr2str(int len, int nbr, char *s);
void		add_log_msg(t_pdata *b, int type, int meal);

// log_utils2.c

void		print_msg(t_logmsg *msg, char *init);
int			print_log(t_log *log, pthread_mutex_t *mtx);
int			ya_power(int nbr, int pow);

#endif	/* PHILO_H */