#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

int	get_ms_difff(struct timeval *t1, struct timeval *t2, int now)
{
	if (now)
		gettimeofday(t2, NULL);
	now = (t2->tv_sec - t1->tv_sec) * 10000;
	now += (t2->tv_usec - t1->tv_usec) / 100;
	return (now);
}

void	rrsleep(int ms)
{
	struct timeval	tv[2];

	gettimeofday(&tv[0], NULL);
	usleep(250);
	while (get_ms_diff(&tv[0], &tv[1], 1) < (ms * 10))
		usleep(250);
}

int main(int ac, char **ag)
{
	struct timeval	tv[2];

	gettimeofday(&tv[0], NULL);
	while (0)
	{
		//usleep(200000);
		rsleep(200);
		printf("%dms\n", get_ms_diff(&tv[0], &tv[1], 1));
	}
	char	s[80];
	for (int i = 0; i < 80; i++)
		s[i] = 0;
	//nbr2str(10, 56789, s);
	//printf("%s\n", s);
	t_pdata brain;
	brain.name = 2;
	gettimeofday(&(brain.start), NULL);
	usleep(10000);
	gettimeofday(&(brain.now), NULL);
	log_msg(&brain, " is eating\n", NULL);
	printf("%s\n", brain.msg);
	(void)ac;
	printf("[%d][%d]\n", read_args(ag, 1), read_args(ag, 2));
}