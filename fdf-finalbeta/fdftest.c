/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdftest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:28:52 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/05 17:13:02 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bits_ppx / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(int x[2], int y[2], t_data *img)
{
    int dx = abs(x[1] - x[0]);
    int dy = abs(y[1] - y[0]);
    int sx = x[0] < x[1] ? 1 : -1;
    int sy = y[0] < y[1] ? 1 : -1;
    int err = dx - dy;
    
    while (x[0] != x[1] || y[0] != y[1]) {
        my_mlx_pixel_put(img, x[0], y[0], 0x000000FF);
        int e2 = 2 * err;
        if (e2 > -dy)
		{
            err -= dy;
            x[0] += sx;
        }
        if (e2 < dx)
		{
            err += dx;
            y[0] += sy;
        }
    }
    my_mlx_pixel_put(img, x[1], y[1], 0x000000FF);
}

void	norm_line(int xy[4], int argb, t_data *img)
{
	int	ds_xy[4];
	int	err[2];

	ds_xy[0] = abs(xy[2] - xy[0]);
	ds_xy[1] = abs(xy[3] - xy[1]);
	if (xy[0] < xy[2])
		ds_xy[2] = 1;
	else
		ds_xy[2] = -1;
	if (xy[1] < xy[3])
		ds_xy[3] = 1;
	else
		ds_xy[3] = -1;
	err[0] = ds_xy[0] - ds_xy[1];
	while (xy[0] != xy[2] || xy[1] != xy[3])
	{
		my_mlx_pixel_put(img, xy[0], xy[1], argb);
		err[1] = 2 * err[0];
		if (err[1] > -ds_xy[1])
		{
			err[0] -= ds_xy[1];
			xy[0] += ds_xy[2];
		}
		if (err[1] < ds_xy[0])
		{
			err[0] += ds_xy[0];
			xy[1] += ds_xy[3];
		}
	}
	my_mlx_pixel_put(img, xy[2], xy[3], argb);
}

int	closewin(int keycode, void *mlx, void *win)
{
	(void)keycode;
	mlx_destroy_window(mlx, win);
	exit (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook! [%d]\n", keycode);
	if (keycode == 53)
		printf("ESC");
	if (keycode == 53)
	{
		closewin(keycode, vars->mlx, vars->win);
		exit (0);
	}
	return (0);
}

int	mousemove_hook(int x, int y, t_vars *vars)
{
	if (vars->mbutton > 0)
	{
		my_mlx_pixel_put(vars->img, x, y, 0x00FFFFFF);
		mlx_put_image_to_window(vars->mlx, vars->win, (*vars).img->img, 0, 0);
	}
	return (0);
}

int	mousebutton_hook(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (vars->mbutton == button)
		vars->mbutton = 0;
	else
	{
		printf("Mouse button %d pressed\n", button);
		vars->mbutton = button;
	}
	return (0);
}

double	get_time()
{
	unsigned long long	cycles;
	double				seconds;

    __asm__ volatile	("rdtsc" : "=A" (cycles));
	seconds = (double) cycles / 2.8e9;
	return (seconds);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world");
	vars.mbutton = 0;
	vars.refresh = 0;
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_ppx, &img.len, &img.endian);
	vars.img = &img;
	for (int i = 5; i < 1075; i++)
		my_mlx_pixel_put(&img, i, i, 0x00FF0000);
	for (int i = 5; i < 1500; i++)
		for (int j = 5; j < 30; j++)
			my_mlx_pixel_put(&img, i+(j*20), j*20, 0x0000FF00 + (j*10));
	draw_line((int [2]){100, 1300}, (int [2]){100, 800}, &img);
	draw_line((int [2]){100, 1820}, (int [2]){540, 600}, &img);
	for (int i = 0; i < 100; i++)
		norm_line((int[4]){20 + i, 1720 + i, 20 + (i*10), 400 + (i * 5)}, 0x0000FF00, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, closewin, &vars);
	mlx_hook(vars.win, 6, 0, mousemove_hook, &vars);
	mlx_hook(vars.win, 4, 0, mousebutton_hook, &vars);
	mlx_hook(vars.win, 5, 0, mousebutton_hook, &vars);
	//mlx_hook(vars.win, 2, 1L << 0, closewin, &vars);
	mlx_loop(vars.mlx);
}
