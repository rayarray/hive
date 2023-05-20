/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:15:01 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/19 12:36:54 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init(t_fdf *fdf)
{
	fdf->vx = (fdf->wx * 10);
	//fdf->vy = (fdf->wy * 10) + ((fdf->zoom * fdf->wy) / (fdf->wx / 100));
	fdf->vy = (fdf->wy * 10);
	fdf->zadj = 0;
	fdf->xyadj[0] = 0;
	fdf->xyadj[1] = 0;
	fdf->bgcolor = 0x000A2030;
	fdf->vars.mbutton = 0;
	fdf->rot2 = 45;
	fdf->pln = 45;
	// rot2 = 0 and zscale = 300, testing new projection (draw_fdf2)
	ft_printf("abs(max - min):%d\n", abs(fdf->map->max - fdf->map->min));
	if (abs(fdf->map->max - fdf->map->min) >= 99)
		fdf->zscale = 25;
	else if (abs(fdf->map->max - fdf->map->min) >= 49)
		fdf->zscale = 50;
	else if (abs(fdf->map->max - fdf->map->min) >= 24)
		fdf->zscale = 75;
	else
		fdf->zscale = 90;
}

void	rotate_xy(t_fdf *fdf, int xy[3], int x, int y)
{
	double	rx;
	double	ry;
	double	angle;

	x = xy[0] - (fdf->wx / 2);
	y = xy[1] - (fdf->wy / 2);
	angle = fdf->rot2 * M_PI / 180;
	rx = x * cos(angle) - y * sin(angle);
	ry = x * sin(angle) + y * cos(angle);
	rx += (fdf->wx) / 2;
	ry += (fdf->wy) / 2;
	xy[0] = (int)rx;
	xy[1] = (int)ry;
}

void	chk_rotate(t_fdf *fdf)
{
	if (fdf->rot2 >= 90)
	{
		fdf->rot2 -= 90;
		if (++(fdf->rot) > 3)
			fdf->rot = 0;
	}
	else if (fdf->rot2 <= -90)
	{
		fdf->rot2 += 90;
		if (--(fdf->rot) < 0)
			fdf->rot = 3;
	}
}