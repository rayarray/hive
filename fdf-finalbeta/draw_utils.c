/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:07:51 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/19 14:42:46 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	chk_visible(t_fdf *fdf, int xy[4])
{
	t_rgbline	ln;

	ln.dx = abs(xy[2] - xy[0]);
	ln.dy = abs(xy[3] - xy[1]);
	if (xy[0] < xy[2])
		ln.sx = 1;
	else
		ln.sx = -1;
	if (xy[1] < xy[3])
		ln.sy = 1;
	else
		ln.sy = -1;
	ln.err = ln.dx - ln.dy;
	while (1)
	{
		if (xy[0] > -1 && xy[0] < fdf->wx && xy[1] > -1 && xy[1] < fdf->wy)
			return (1);
		if (xy[0] == xy[2] && xy[1] == xy[3])
			break ;
		ln.err2 = 2 * ln.err;
		if (ln.err2 > -ln.dy)
		{
			ln.err -= ln.dy;
			xy[0] += ln.sx;
		}
		if (ln.err2 < ln.dx)
		{
			ln.err += ln.dx;
			xy[1] += ln.sy;
		}
	}
	return (0);
}

/* void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x > -1 && x < fdf->wx && y > -1 && y < fdf->wy)
	{
		dst = fdf->img.addr + (y * fdf->img.len + x * (fdf->img.bits_ppx / 8));
		*(unsigned int *)dst = color;
	}
} */

void	put_pixel(t_fdf *fdf, int x, int y, unsigned int color)
{
	char	*dst;

	if (x > -1 && x < fdf->wx && y > -1 && y < fdf->wy)
	{
		dst = fdf->img.addr + (y * fdf->img.len + x * (fdf->img.bits_ppx / 8));
		*(unsigned int *)dst = color;
	}
}

/* void	rotate_px(t_fdf *fdf, int x, int y, unsigned int color)
{
	double	rx;
	double	ry;
	double	angle;

	x -= (fdf->wx) / 2;
	y -= (fdf->wy) / 2;
	angle = fdf->rot2 * M_PI / 180;
	rx = x * cos(angle) - y * sin(angle);
	ry = x * sin(angle) + y * cos(angle);
	rx += (fdf->wx) / 2;
	ry += (fdf->wy) / 2;

	put_pixel(fdf, (int)rx, y, color);
} */

/* void	norm_line(int xy[4], int argb, t_fdf *fdf)
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
		my_mlx_pixel_put(fdf, xy[0], xy[1], argb);
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
	my_mlx_pixel_put(fdf, xy[2], xy[3], argb);
} */

void	grad_line2(t_rgbline *ln, t_fdf *fdf)
{
	ln->dx = abs(ln->x2 - ln->x1);
	ln->dy = abs(ln->y2 - ln->y1);
	if (ln->x1 < ln->x2)
		ln->sx = 1;
	else
		ln->sx = -1;
	if (ln->y1 < ln->y2)
		ln->sy = 1;
	else
		ln->sy = -1;
	ln->err = ln->dx - ln->dy;
	while (ln->x1 != ln->x2 || ln->y1 != ln->y2)
	{
		ln->rgb2 = ln->rgb;
		ln->rgb2 += ((ln->rd * ((++(ln->pos) * 10) / ln->len)) / 10) << 16;
		//ft_printf("rgb2:%x\n", ((ln->rd * ((++(ln->pos) * 10) / ln->len)) / 10) << 16);
		ln->rgb2 += ((ln->gd * ((ln->pos * 10) / ln->len)) / 10) << 8;
		ln->rgb2 += ((ln->bd * ((ln->pos * 10) / ln->len)) / 10);
		//ft_printf("%x\n", ln->rgb2);
		put_pixel(fdf, ln->x1, ln->y1, ln->rgb2);
		//rotate_px(fdf, ln->x1, ln->y1, ln->rgb2);
		ln->err2 = 2 * ln->err;
		if (ln->err2 > -ln->dy)
		{
			ln->err -= ln->dy;
			ln->x1 += ln->sx;
		}
		if (ln->err2 < ln->dx)
		{
			ln->err += ln->dx;
			ln->y1 += ln->sy;
		}
	}
	//ft_printf("ln->len:%d ln->pos:%d\n", ln->len, ln->pos);
	put_pixel(fdf, ln->x2, ln->y2, ln->rgb + ln->rd + ln->gd + ln->bd);
}

void	grad_line(int xy[4], int argb, int argb2, t_fdf *fdf)
{
	t_rgbline	*ln;

	ln = &fdf->ln;
	//if (argb != argb2)
	//	ft_printf("argb:%x arbg2:%x\n", argb, argb2);
	if ((xy[0] < 0 || xy[2] > (fdf->wx)))
		return ;
	ln->x1 = xy[0];
	ln->x2 = xy[2];
	ln->y1 = xy[1];
	ln->y2 = xy[3];
	ln->rgb = argb;
	ln->rd = ((argb2 & 0xFF0000) - (argb & 0xFF0000)) >> 16;
	ln->gd = (argb2 >> 8 & 0xFF) - (argb >> 8 & 0xFF);
	ln->bd = (argb2 & 0xFF) - (argb & 0xFF);
	ln->len = minmax(2, abs(xy[0] - xy[2]), abs(xy[1] - xy[3]));
	//ln->len = get_pxinline(xy);
	ln->pos = 0;
	grad_line2(ln, fdf);
	//norm_line(xy, argb2, &fdf->img);
}
