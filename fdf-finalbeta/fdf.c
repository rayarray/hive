/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:19:01 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/19 14:56:55 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_args(int ac, char **av)
{
	if (ac < 0)
	{
		perror("Error");
		return (0);
	}
	if (ac == 1)
		ft_printf("Please specify a map file to open\n");
	else if (ac > 2)
		ft_printf("Too many arguments\n");
	else if (ac == 2 && ft_strncmp(".fdf", av[1] + ft_strlen(av[1]) - 4, 4))
		ft_printf("File name must end in .fdf\n");
	else
		return (1);
	return (0);
}

void	redraw_win(t_fdf *fdf)
{
	clr_image(fdf, fdf->bgcolor);
	//mlx_put_image_to_window(fdf->vars.mlx, fdf->vars.win, fdf->img.img, 0, 0);
	draw_image(fdf);
	//draw_box(fdf, (int [4]){5, 3, 235, 66}, 0x00000000);
	//draw_box(fdf, (int [4]){5, 3, 235, 66}, 0xF02070A0);
	mlx_put_image_to_window(fdf->vars.mlx, fdf->vars.win, fdf->img.img, 0, 0);
	draw_ui(fdf);
}

int	mousemove_hook(int x, int y, t_fdf *fdf)
{
	if (fdf->vars.mbutton == 1 && (1 || x))
	{
		if (x - fdf->vars.mx >= 360)
		{
			fdf->rot += 1;
			if (fdf->rot > 3)
				fdf->rot -= 4;
			fdf->vars.mx += 360;
		}
		else if (x - fdf->vars.mx <= -360)
		{
			fdf->rot -= 1;
			if (fdf->rot < 0)
				fdf->rot += 4;
			fdf->vars.mx -= 360;
		}
		fdf->rot2 = (x - fdf->vars.mx) / 4;
		fdf->pln = (y - fdf->vars.my) / 4;
		redraw_win(fdf);
	}
	return (0);
}

int	mousebutton_hook(int button, int x, int y, t_fdf *fdf)
{
	if (fdf->vars.mbutton == button && (1 || x))
		fdf->vars.mbutton = 0;
	else
		fdf->vars.mbutton = button;
	if (button == 1)
	{
		fdf->vars.mx = x - (fdf->rot2 * 4);
		fdf->vars.my = y - (fdf->pln * 4);
	}
	return (0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 12 || keycode == 14)
	{
		if (keycode == 14 && ++(fdf->rot) == 4)
			fdf->rot = 0;
		if (keycode == 12 && --(fdf->rot) == -1)
			fdf->rot = 3;
		redraw_win(fdf);
	}
	else if (keycode == 69 || keycode == 78)
	{
		if (keycode == 69)
			fdf->zadj += 5;
		else
			fdf->zadj -= 5;
		redraw_win(fdf);
	}
	else if (keycode == 6 || keycode == 7)
	{
		if (keycode == 6)
		{
			fdf->vx = (fdf->vx * 11) / 10;
			fdf->vy = (fdf->vy * 11) / 10;
		}
		else
		{
			fdf->vx = (fdf->vx * 9) / 10;
			fdf->vy = (fdf->vy * 9) / 10;
		}
		redraw_win(fdf);
	}
	else if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
	{
		if (keycode == 13)
			fdf->xyadj[1] += 50;
		if (keycode == 1)
			fdf->xyadj[1] -= 50;
		if (keycode == 0)
			fdf->xyadj[0] += 50;
		if (keycode == 2)
			fdf->xyadj[0] -= 50;
		redraw_win(fdf);
	}
	else if (keycode == 123 || keycode == 124)
	{
		if (keycode == 123)
			fdf->rot2 += 10;
	}
	else if (keycode == 15)
	{
		fdf_init(fdf);
		redraw_win(fdf);
	}
	else if (keycode == 53 || keycode == 8)
	{
		ft_printf("Closing window\n");
		mlx_destroy_window(fdf->vars.mlx, fdf->vars.win);
		exit (0);
	}
	else
		ft_printf("Key pressed, keycode %d", keycode);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf		fdf;
	extern int	errno;

	if (check_args(ac, av) == 0)
		return (0);
	fdf.fd = open(av[1], O_RDWR);
	if (fdf.fd == -1 && errno == EISDIR)
		return (check_args(-1, NULL));
	else
		fdf.fd = open(av[1], O_RDONLY);
	if (fdf.fd == -1)
		return (check_args(-1, NULL));
	fdf.map = readmap(fdf.fd);
	if (close(fdf.fd))
		return (check_args(-1, NULL));
	fdf.wx = 1920;
	fdf.wy = 1080;
	fdf.rot = 0;
	fdf_init(&fdf);
	fdf.vars.mlx = mlx_init();
	fdf.vars.win = mlx_new_window(fdf.vars.mlx, fdf.wx, fdf.wy, "fdf");
	fdf.img.img = mlx_new_image(fdf.vars.mlx, fdf.wx, fdf.wy);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bits_ppx, &fdf.img.len, &fdf.img.endian);
	fdf.vars.img = &(fdf.img);
	redraw_win(&fdf);
	mlx_key_hook(fdf.vars.win, key_hook, &fdf);
	mlx_hook(fdf.vars.win, 4, 0, mousebutton_hook, &fdf);
	mlx_hook(fdf.vars.win, 5, 0, mousebutton_hook, &fdf);
	mlx_hook(fdf.vars.win, 6, 0, mousemove_hook, &fdf);
	mlx_loop(fdf.vars.mlx);
}
