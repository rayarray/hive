#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "fdf.h"

int	main(void)
{
	// ft_printf("hex_atoi 0:%d\n", hex_atoi("0", 0));
	// ft_printf("hex_atoi 1:%d\n", hex_atoi("1", 0));
	// ft_printf("hex_atoi 10:%d\n", hex_atoi("10", 0));
	// ft_printf("hex_atoi 1000:%d\n", hex_atoi("1000", 0));
	// ft_printf("hex_atoi FFF:%d\n", hex_atoi("FFF", 0));

	int fd = open("test.fdf", O_RDONLY);
	if (fd == -1) {
		ft_printf("open() error\n");
		return (1);
	}
	t_map *map = readmap(fd);
	if (close(fd) == -1) {
		ft_printf("close () error\n");
		return (1);
	}
	ft_printf("map(2, 1) = %d\n", map->z[0][1]);
	ft_printf("map x=%d y=%d", map->col, map->row);
	//ft_printf("");
	int x, y = 0;
	char sp = ' ';
	char nl = '\n';
	while (y < (map->row))
	{
		x = 0;
		while (x < (map->col))
		{
			ft_printf("%d", map->z[y][x]);
			if (map->rgb[y][x] != 0x00FFFFFF)
				ft_printf(",%x", map->rgb[y][x]);
			//ft_printf("%d", *((*(map->data+y))+x));
			//s = ft_itoa(*((*(map->data+y))+x));
			//write(1, s, ft_strlen(s));
			x++;
			if (x < (map->col))
				write(1, &sp, 1);
		}
		write(1, &nl, 1);
		y++;
	}
	y = map->row;
	/* while (y-- > 0)
	{
		free(map->y[y]);
	}
	free (map->y);
	free (map->rgb);
	free (map); */
}