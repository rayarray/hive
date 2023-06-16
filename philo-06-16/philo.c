/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:30:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/16 16:48:46 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_old(void *arg)
{
	struct timeval	tv;
	int				i;

	(void)arg;
	i = 0;
	while (i < 200)
	{
		pthread_mutex_lock((pthread_mutex_t *)arg);
		i++;
		pthread_mutex_unlock((pthread_mutex_t *)arg);
		usleep(i);
	}
	gettimeofday(&tv, NULL);
	printf("Thread exiting at %lds%dms\n", tv.tv_sec, tv.tv_usec);
	pthread_exit(NULL);
}

void	*philosopher(void *arg)
{
	t_pdata	*brain;

	brain = arg;
	gettimeofday(&(brain->start), NULL);
	gettimeofday(&(brain->lastmeal), NULL);
	while (*(brain->death) == 0)
	{
		printf("%9dms: Philo %2d started thinking\n", get_ms_diff(&(brain->start), &(brain->now), 1), brain->name);
		manage_forks(brain, 1);
		if (get_ms_diff(&brain->lastmeal, &brain->now, 1) > brain->starve)
		{
			printf("%9dms: Philo %2d DIED\n", get_ms_diff(&brain->start, &brain->now, 0), brain->name);
			*(brain->death) = brain->name;
			manage_forks(brain, 0);
			pthread_exit(NULL);
		}
		gettimeofday(&(brain->lastmeal), NULL);
		printf("%9dms: Philo %2d started eating the %dth meal\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name, ++(brain->meals));
		rsleep(brain->eat_dur);
		manage_forks(brain, 0);
		printf("%9dms: Philo %2d started sleeping\n", get_ms_diff(&brain->start, &brain->now, 1), brain->name);
		rsleep(brain->slp_dur);
	}
	pthread_exit(NULL);
}

int	commence_philosophy(int size, pthread_t *philos, pthread_mutex_t *forks,
	t_pdata *brains)
{
	int	result;
	int	i;

	i = -1;
	while (++i < size)
		pthread_mutex_init(forks + i, NULL);
	i = 0;
	while (++i <= size)
	{
		if (i < size)
			result = pthread_create(philos + i, NULL, philosopher,
					make_brain(i, brains, forks, 0));
		else
			result = pthread_create(philos + i, NULL, philosopher,
					make_brain(i, brains, forks, 1));
		if (result)
			printf("Thread creation failed\n");
		result = pthread_detach(*(philos + i));
		if (result)
			printf("Thread detach failed\n");
	}
	return (1);
}

int	main(int ac, char **ag)
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	t_pdata			*brains;
	int				death;

	(void)ag;
	death = 0;
	philos = (pthread_t *)malloc(sizeof(pthread_t) * 50);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (50 + 1));
	brains = (t_pdata *)malloc(sizeof(t_pdata) * (50 + 1));
	brains->meals = 0;
	brains->eat_dur = 200;
	brains->slp_dur = 100;
	brains->starve = 310;
	brains->death = &death;
	commence_philosophy(4, philos, forks, brains);
	while (death == 0)
		;
	// pthread_mutex_init(&mutex, NULL);
	// result = pthread_create(&thread, NULL, philosopher, &mutex);
	// if (result)
	// {
	// 	printf("Thread creation failed with result %d\n", result);
	// 	return (0);
	// }
	// result = pthread_detach(thread);
	// if (result)
	// {
	// 	printf("Thread detach failed with result %d\n", result);
	// 	return (0);
	// }
	// result = pthread_create(&thread2, NULL, philosopher, &mutex);
	// if (result)
	// {
	// 	printf("Thread creation failed with result %d\n", result);
	// 	return (0);
	// }
	// pthread_join(thread, NULL);
	// pthread_join(thread2, NULL);
	//usleep(10000);
	return (ac);
}
