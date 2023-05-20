/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:30:42 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/19 14:56:40 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	getxy(t_fdf *fdf, int rot, int xy[2], int val)
{
	if ((val == 2 && (rot == 0 || rot == 2)) || (val == 3 && (rot == 1 || rot == 3)))
		return (fdf->map->col);
	else if (val == 2 || val == 3)
		return (fdf->map->row);
	if (val == 0 && rot == 0)
		return (fdf->map->z[xy[1]][xy[0]]);
	if (val == 0 && rot == 1)
		return (fdf->map->z[fdf->map->row - xy[0] - 1][xy[1]]);
	if (val == 0 && rot == 2)
		return (fdf->map->z[fdf->map->row - xy[1] - 1]
			[fdf->map->col - xy[0] - 1]);
	if (val == 0 && rot == 3)
		return (fdf->map->z[xy[0]][fdf->map->col - xy[1] - 1]);
	if (val == 1 && rot == 0)
		return (fdf->map->rgb[xy[1]][xy[0]]);
	if (val == 1 && rot == 1)
		return (fdf->map->rgb[fdf->map->row - xy[0] - 1][xy[1]]);
	if (val == 1 && rot == 2)
		return (fdf->map->rgb[fdf->map->row - xy[1] - 1]
			[fdf->map->col - xy[0] - 1]);
	if (val == 1 && rot == 3)
		return (fdf->map->rgb[xy[0]][fdf->map->col - xy[1] - 1]);
	return (-1);
}

void	rot_xy(t_fdf *fdf, int x, int y)
{
	// int	sx;
	// int	sy;
	
	// sx = (x - (getxy(fdf, fdf->rot, NULL, 2) / 2)) * fdf->xlen / 10;
	// sy = (y - (getxy(fdf, fdf->rot, NULL, 3) / 2)) * fdf->ylen / 10;
	x = x * 6 - (getxy(fdf, fdf->rot, NULL, 2) * 3) + 3;
	y = y * 6 - (getxy(fdf, fdf->rot, NULL, 3) * 3) + 3;
	//x = x * 6 - (fdf->map->col * 3) + 3;
	//y = y * 6 - (fdf->map->row * 3) + 3;
	//fdf->angle = fdf->rot2 * M_PI / 180;
	fdf->rx = x * cos(fdf->rrad) - y * sin(fdf->rrad);
	fdf->ry = x * sin(fdf->rrad) + y * cos(fdf->rrad);
	fdf->rx = (fdf->rx + (getxy(fdf, fdf->rot, NULL, 2) * 3)) - 3;
	fdf->ry = (fdf->ry + (getxy(fdf, fdf->rot, NULL, 3) * 3)) - 3;
	//fdf->rx = (fdf->rx + (fdf->map->col * 3)) - 3;
	//fdf->ry = (fdf->ry + (fdf->map->row * 3)) - 3;
	//fdf->rx += (x - (getxy(fdf, fdf->rot, NULL, 2) / 2)) * fdf->xlen / 10;
	//fdf->ry += (y - (getxy(fdf, fdf->rot, NULL, 3) / 2)) * fdf->ylen / 10;
}

void	get_visible(t_fdf *fdf, double wxy[4], int x, int y)
{
	while (y < getxy(fdf, fdf->rot, NULL, 3))
	{
		rot_xy(fdf, 0, y);
		wxy[0] = get_wxy(fdf, 0, y, 0);
		wxy[1] = get_wxy(fdf, 0, y, 1);
		rot_xy(fdf, x, y);
		wxy[2] = get_wxy(fdf, x, y, 0);
		wxy[3] = get_wxy(fdf, x, y, 1);
		if (chk_vposs(fdf, wxy) && chk_visible(fdf, (int [4]){wxy[0], wxy[1], wxy[2], wxy[3]}))
			break ;
		y++;
	}
	fdf->vrow[0] = minmax(2, 0, y - 1);
	y = getxy(fdf, fdf->rot, NULL, 3) - 1;
	while (y > fdf->vrow[0])
	{
		rot_xy(fdf, 0, y);
		wxy[0] = get_wxy(fdf, 0, y, 0);
		wxy[1] = get_wxy(fdf, 0, y, 1);
		rot_xy(fdf, x, y);
		wxy[2] = get_wxy(fdf, x, y, 0);
		wxy[3] = get_wxy(fdf, x, y, 1);
		if (chk_vposs(fdf, wxy) && chk_visible(fdf, (int [4]){wxy[0], wxy[1], wxy[2], wxy[3]}))
			break ;
		y--;
	}
	fdf->vrow[1] = y + 1;
}

void	draw_fdf2(t_fdf *fdf, double wxy[3], int xy[2], int draw)
{
	// double	rot2;
	// double	pln;

	// rot2 = fdf->rot2 * M_PI / 180;
	// pln = fdf->pln * M_PI / 180;
	while (xy[0] < getxy(fdf, fdf->rot, NULL, 2))
	{
		//rot_xy(fdf, xy[0], xy[1]);
		//wxy[0] = fdf->x0 + (fdf->rx / 6) * (fdf->xlen / 10);
		//wxy[1] = fdf->y0 + (fdf->ry / 6) * (fdf->ylen / 10);
		//wxy[1] = (wxy[1] - (fdf->wy / 2)) * sin(fdf->prad) + (fdf->wy / 2);
		wxy[0] = get_wxy(fdf, xy[0], xy[1], 0);
		wxy[1] = get_wxy(fdf, xy[0], xy[1], 1);
		wxy[1] -= cos(fdf->prad) * getxy(fdf, fdf->rot, xy, 0) * (fdf->zscale + fdf->zadj) / 10;
		//wxy[0] += (fdf->wx - (fdf->vx / 10)) / 2 + fdf->xyadj[0];
		//wxy[1] += (fdf->wy - (fdf->vy / 10)) / 2 + fdf->xyadj[1];
		wxy[2] = getxy(fdf, fdf->rot, xy, 1);
		//if (xy[0] == 0 && xy[1] == 0)
		//	printf("x0y0:%f, %f\n", wxy[0], wxy[1]);
		if (draw && xy[1] > 0)
			grad_line((int [4]){*(fdf->cache + (xy[0] * 2)), *(fdf->cache + (xy[0] * 2) + 1),
				wxy[0], wxy[1]}, getxy(fdf, fdf->rot, (int [2]){xy[0], xy[1] - 1}, 1), wxy[2], fdf);
		if (draw && xy[0] > 0)
			grad_line((int [4]){wxy[0], wxy[1], *(fdf->cache + (xy[0] * 2) - 2),
				*(fdf->cache + (xy[0] * 2) - 1)}, wxy[2], getxy(fdf, fdf->rot, (int [2]){xy[0] - 1, xy[1]}, 1), fdf);
		*(fdf->cache + (xy[0] * 2)) = wxy[0];
		*(fdf->cache + (xy[0] * 2) + 1) = wxy[1];
		xy[0]++;
	}
}

void	draw_image(t_fdf *fdf)
{
	t_map	*map;
	int		*colrow;

	map = fdf->map;
	fdf->rrad = fdf->rot2 * M_PI / 180;
	fdf->prad = fdf->pln * M_PI / 180;
	if (fdf->rot == 0 || fdf->rot == 2)
		colrow = (int [2]){map->col, map->row};
	else
		colrow = (int [2]){map->row, map->col};
	fdf->cache = (int *)malloc(sizeof(int) * colrow[0] * 2);
	if (fdf->cache == NULL)
		return ;
	//fdf->x0 = ((colrow[1] - 1) * (fdf->vx / (colrow[0] + colrow[1] - 2))) / 10;
	//fdf->y0 = 0 - (fdf->wx / 10);
	fdf->xlen = fdf->vx / (map->col + map->row - 2);
	fdf->ylen = fdf->xlen;
	//if (colrow[0] > colrow [1])
	//	fdf->ylen = fdf->vy / (colrow[1] - 1);
	//fdf->x0 = ((fdf->vx / 10) - (colrow[0] - 1) * fdf->xlen / 10) / 2;
	//fdf->y0 = ((fdf->vx / 10) - (colrow[1] - 1) * fdf->ylen / 10) / 2;
	//fdf->x0 = ((fdf->vx / 10) - ((colrow[0] - 1) * fdf->xlen / 10)) / 2;
	fdf->x0 = (fdf->vx - ((colrow[0] - 1) * fdf->xlen)) / 20;
	fdf->y0 = (fdf->vy - ((colrow[1] - 1) * fdf->ylen)) / 20;
	//fdf->y0 = ((fdf->vx / 10) - ((colrow[1] - 1) * fdf->ylen / 10)) / 2;
	//printf("wx:%d colrow0:%d xlen:%f x0:%d y0:%d\n", fdf->wx, colrow[0], fdf->xlen, fdf->x0, fdf->y0);
	//printf("min%d max%d\n", fdf->map->min, fdf->map->max);
	// if (colrow[1] > colrow[0])
	// 	fdf->ylen = fdf->xlen;
	// else
	// 	fdf->xlen = fdf->ylen;
	// fdf->ylen = fdf->ylen;
	get_visible(fdf, (double [4]){0, 0, 0, 0}, colrow[0] - 1, 0);
	//ft_printf("vrow:%d, %d\n", fdf->vrow[0], fdf->vrow[1]);
	draw_fdf2(fdf, (double [3]){0, 0, 0}, (int [2]){0, (fdf->vrow[0])++}, 0);
	for (int i = fdf->vrow[0]; i < fdf->vrow[1]; i++)
		draw_fdf2(fdf, (double [3]){0, 0, 0}, (int [2]){0, i}, 1);
	free(fdf->cache);
}

/* void	draw_image(t_fdf *fdf, int rot)
{
	t_map	*map;
	int		*colrow;

	map = fdf->map;
	if (rot == 0 || rot == 2)
		colrow = (int [2]){map->col, map->row};
	else
		colrow = (int [2]){map->row, map->col};
	fdf->cache = (int *)malloc(sizeof(int) * colrow[0] * 2);
	if (fdf->cache == NULL)
		return ;
	//fdf->x0 = (colrow[0] - 1) * ((fdf->vy) / (colrow[0] + colrow[1] - 2));
	//fdf->ylen = ((fdf->vy) - (fdf->x0)) / (colrow[1] - 1);
	fdf->ylen = fdf->vy / (colrow[0] + colrow[1] - 2);
	fdf->x0 = (colrow[1] - 1) * ((fdf->vx) / (colrow[0] + colrow[1] - 2));
	fdf->xlen = ((fdf->vx) - (fdf->x0)) / (colrow[0] - 1);
	//fdf->ylen = ((fdf->vy * 10)) / ((colrow[0] + colrow[1] - 2));
	//fdf->ylen = (fdf->xlen * colrow[1] * fdf->wy) / (fdf->wx * colrow[0]);
	//ft_printf("xlen:%d ylen:%d\n", fdf->xlen, fdf->ylen);
	//ft_printf("mapcol%d maprow%d zscale%d zadj%d\n", colrow[0], colrow[1], fdf->zscale, fdf->zadj);
	//ft_printf("mapcol gxx %d maprow gxy %d\n", getxy(fdf, rot, NULL, 2), getxy(fdf, rot, NULL, 3));
	for (int i = 0; i < colrow[1]; i++)
		draw_fdf2(fdf, (int [3]){0, 0, 0}, (int [2]){0, i}, rot);
	//grad_line((int [4]){200, 10, 700, 50}, 0x00112233, 0x00FFFFFF, fdf);
	//ft_printf("mapmin%d mapmax%d\n", fdf->map->min, fdf->map->max);
	////ft_printf("ymax x0 = %d", fdf->map->y[fdf->map->row - 1][0]);
	free(fdf->cache);
} */

