#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	get_ms_diff(struct timeval *t1, struct timeval *t2, int now)
{
	if (now)
		gettimeofday(t2, NULL);
	now = (t2->tv_sec - t1->tv_sec) * 10000;
	now += (t2->tv_usec - t1->tv_usec) / 100;
	return (now);
}

void	rsleep(int ms)
{
	struct timeval	tv[2];

	gettimeofday(&tv[0], NULL);
	usleep(250);
	while (get_ms_diff(&tv[0], &tv[1], 1) < (ms * 10))
		usleep(250);
}

int main(void)
{
	struct timeval	tv[2];

	gettimeofday(&tv[0], NULL);
	while (1)
	{
		//usleep(200000);
		rsleep(200);
		printf("%dms\n", get_ms_diff(&tv[0], &tv[1], 1));
	}
}