/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:30:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/05 18:27:16 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*waiter(int philo, int *meals)
{
	
}

void	*supervisor(void *arg)
{
	t_pdata			*brain;
	struct timeval	lastmeal;
	struct timeval	timer;
	struct timeval	now;

	brain = (t_pdata *)arg;
	while (brain->launch != NULL)
		usleep(50);
	while (*(brain->death) == 0 && brain->log->sated > 0)
	{
		set_timer(&brain->lastmeal, &lastmeal, 0);
		set_timer(&lastmeal, &timer, brain->starve);
		while (lastmeal.tv_sec == brain->lastmeal.tv_sec && lastmeal.tv_usec
			== brain->lastmeal.tv_usec && *(brain->death) == 0
			&& brain->log->sated > 0)
		{
			if (!chk_timer(&timer, &now))
				usleep(1000);
			else if (*(brain->death) == 0 && brain->log->sated > 0)
				add_log_msg(brain, PHILO_DEAD, 0);
		}
	}
	pthread_exit(NULL);
}

void	*philosopher(void *arg)
{
	t_pdata			*brain;
	struct timeval	eatslp[2];

	brain = (t_pdata *)arg;
	brain = philostart(NULL, arg);
	while (*(brain->death) == 0)
	{
		add_log_msg(brain, PHILO_THINKING, 0);
		manage_forks(brain, 1);
		gettimeofday(&(brain->lastmeal), NULL);
		set_timer(&(brain->lastmeal), &eatslp[0], brain->eat_dur);
		add_log_msg(brain, PHILO_EATING, ++(brain->meals));
		wait_timer(&eatslp[0], &eatslp[1]);
		manage_forks(brain, 0);
		if (brain->meals == brain->full)
			break ;
		set_timer(&eatslp[1], &eatslp[0], brain->slp_dur);
		add_log_msg(brain, PHILO_SLEEPING, 0);
		wait_timer(&eatslp[1], &eatslp[0]);
		usleep(brain->wait);
	}
	if (brain->meals == brain->full)
		add_log_msg(brain, PHILO_SATED, 0);
	pthread_exit(NULL);
}

int	commence_philosophy(t_table *t)
{
	int	result;
	int	i;

	i = -1;
	while (++i <= t->philos + 1)
	{
		result = pthread_mutex_init((t->f)[i], NULL);
		if (result)
			printf("Mutex creation error %d\n", result);
	}
	i = 0;
	while (++i <= t->philos)
		make_brain(i, t->b, t->f, i / t->philos);
	while (--i >= 0)
		(t->b + i)->super = t->sv + i - 1;
	while (++i < t->philos)
	{
		result = pthread_create(t->p + i, NULL, philosopher, t->b + i + 1);
		if (result)
			printf("Thread creation failed\n");
		result = pthread_detach(*(t->p + i));
		if (result)
			printf("Thread detach failed\n");
	}
	return (1);
}

int	main(int ac, char **ag)
{
	t_table	t;

	if (chk_args(ac, ag) == -1 || read_args(ag, 1) == 0)
		return (0);
	if (init_table(&t, ag, ac, -1) == 1)
	{
		commence_philosophy(&t);
		while (print_log(t.b->log, *(t.f)))
			usleep(250);
	}
	while (t.i-- > 0)
		pthread_join(*(t.sv + t.i), NULL);
	t.i = t.philos;
	while (t.i-- > 0)
		pthread_join(*(t.p + t.i), NULL);
	if (t.p != NULL)
		free (t.p);
	if (t.sv != NULL)
		free (t.sv);
	if (t.b->log != NULL)
		free (t.b->log);
	if (t.b != NULL)
		free (t.b);
	return (0);
}
