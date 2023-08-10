/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:53:29 by rleskine          #+#    #+#             */
/*   Updated: 2023/08/05 17:49:30 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	chk_args(int ac, char **ag)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: philos a b c d [e]\n\nWhere a is the number of philosop");
		printf("hers, b is the time they can survive between\nmeals (counted");
		printf(") from the start of the meal), c is the time it takes to eat\n");
		printf("and d is the time it takes to sleep. Optionally [e] can be s");
		printf("pecified as the\n");
		printf("number of meals each philosopher can eat before stopping\n");
		return (-1);
	}
	if (read_args(ag, 1) == -1 || read_args(ag, 2) == -1
		|| read_args(ag, 3) == -1 || read_args(ag, 4) == -1)
	{
		printf("Invalid argument. Numeric values [0-9] only!\n");
		return (-1);
	}
	if (ac == 6 && read_args(ag, 5) == -1)
	{
		printf("Invalid argument. Numeric values [0-9] only!\n");
		return (-1);
	}
	return (1);
}

void	set_timer(struct timeval *time, struct timeval *timer, int ms)
{
	if (time && time != timer)
	{
		timer->tv_sec = time->tv_sec;
		timer->tv_usec = time->tv_usec;
	}
	else
		gettimeofday(timer, NULL);
	timer->tv_usec += ms * 1000;
	while (timer->tv_usec > 1000000)
	{
		(timer->tv_sec)++;
		timer->tv_usec -= 1000000;
	}
}

int	chk_timer(struct timeval *timer, struct timeval *now)
{
	gettimeofday(now, NULL);
	if (timer->tv_sec < now->tv_sec || (timer->tv_sec == now->tv_sec
			&& timer->tv_usec <= now->tv_usec))
		return (1);
	return (0);
}

void	wait_timer(struct timeval *timer, struct timeval *now)
{
	int	wait_time;

	if (chk_timer(timer, now))
		return ;
	wait_time = ((timer->tv_sec % 100) * 1000000 + timer->tv_usec);
	wait_time -= ((now->tv_sec % 100) * 1000000 + now->tv_usec);
	if (wait_time <= 0)
		return ;
	else if (wait_time > 6000)
		usleep(wait_time - (wait_time / 10));
	while (!chk_timer(timer, now))
		usleep(250);
}
