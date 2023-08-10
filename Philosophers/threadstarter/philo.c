/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:30:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/10 11:20:14 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threadfunc(void *arg)
{
	t_pdata *b;

	b = (t_pdata *)arg;
	printf("thread %d started\n", b->name);
	usleep(100000);
	printf("thread %d exiting\n", b->name);
	pthread_exit(NULL);
}

int	commence_philosophy(t_table *t)
{
	int	result;
	int	i;

	// i = -1;
	// while (++i <= t->philos + 1)
	// {
	// 	result = pthread_mutex_init((t->f)[i], NULL);
	// 	if (result)
	// 		printf("Mutex creation error %d\n", result);
	// }
	i = 0;
	while (++i <= t->philos)
		make_brain(i, t->b, t->f, t->philos);
	//while (--i >= 0)
	//	(t->b + i)->super = t->sv + i - 1;
	i = -1;
	while (++i < t->philos)
	{
		//printf("creating thread %d\n", i);
		result = pthread_create(t->p + i, NULL, threadfunc, t->b + i + 1);
		if (result)
			printf("Thread creation failed\n");
		//result = pthread_detach(*(t->p + i));
		//if (result)
		//	printf("Thread detach failed\n");
	}
	return (1);
}

// int	init_table(t_table *t, char **ag, int ac, int i)
// {
// 	t->philos = read_args(ag, 1);
// 	t->p = (pthread_t *)malloc(sizeof(pthread_t) * (t->philos));
// 	t->sv = (pthread_t *)malloc(sizeof(pthread_t) * (t->philos));
// 	t->b = (t_pdata *)malloc(sizeof(t_pdata) * (t->philos + 1));
// 	t->f = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
// 			* (t->philos + 2));
// 	if (t->p == NULL || t->sv == NULL || t->b == NULL || t->f == NULL)
// 		return (0);
// 	t->i = t->philos;
// 	while (++i <= t->philos + 1)
// 		t->f[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
// 	t->b->full = -1;
// 	if (ac == 6)
// 		t->b->full = read_args(ag, 5);
// 	t->b->eat_dur = read_args(ag, 3);
// 	t->b->slp_dur = read_args(ag, 4);
// 	t->b->starve = read_args(ag, 2);
// 	t->b->log = init_log(t->philos);
// 	if (t->b->log == NULL)
// 		return (0);
// 	t->b->death = &t->death;
// 	t->b->log_mtx = t->f[0];
// 	t->death = 0;
// 	//t->b->wait = t->b->starve - (t->b->eat_dur + t->b->slp_dur);
// 	return (1);
// }

int	main(int ac, char **ag)
{
	t_table	t;

	if (ac < 2)
		return (0);
	t.philos = read_args(ag, 1);
	printf("starting %d threads\n", t.philos);
	t.p = (pthread_t *)malloc(sizeof(pthread_t) * (t.philos));
	if (t.p == NULL)
		return (0);
	t.b = (t_pdata *)malloc(sizeof(t_pdata) * (t.philos + 1));
	if (t.b == NULL)
		return (0);
	commence_philosophy(&t);
	while (t.philos-- > 0)
		pthread_join(*(t.p + t.philos), NULL);
	
	
	// if (chk_args(ac, ag) == -1 || read_args(ag, 1) == 0)
	// 	return (0);
	// if (init_table(&t, ag, ac, -1) == 1)
	// {
	// 	commence_philosophy(&t);
	// 	while (print_log(t.b->log, *(t.f)))
	// 		usleep(1000);
	// }
	// while (t.i-- > 0)
	// 	pthread_join(*(t.sv + t.i), NULL);
	// t.i = t.philos;
	// while (t.i-- > 0)
	// 	pthread_join(*(t.p + t.i), NULL);
	// if (t.p != NULL)
	// 	free (t.p);
	// if (t.sv != NULL)
	// 	free (t.sv);
	// if (t.b->log != NULL)
	// 	free (t.b->log);
	// if (t.b != NULL)
	// 	free (t.b);
	// ac = -1;
	// while (t.f && ++ac <= t.philos + 1 && t.f[ac] != NULL)
	// 	pthread_mutex_destroy(t.f[ac]);
	// ac = -1;
	// while (t.f && ++ac <= t.philos + 1 && t.f[ac] != NULL)
	// 	free(t.f[ac]);
	// if (t.f != NULL)
	// 	free (t.f);
	// return (0);
}
