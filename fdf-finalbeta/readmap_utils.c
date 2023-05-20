/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:00:37 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/12 10:27:41 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_rowsize(char *line, int x)
{
	while (line && *line != 0 && *line != '\n')
	{
		while (*line == ' ')
			line++;
		while (*line != ' ' && *line != '\n' && *line != 0)
			line++;
		while (*line == ' ' && *line != '\n' && *line != 0)
			line++;
		x++;
	}
	return (x);
}

char	*parse_value(char *line, int *val, int *rgb)
{
	if (line && *line == '0' && *(line + 1) == 'x')
	{
		line += 2;
		*val = hex_atoi(line, 0);
		while (ft_ishex(*line))
			line++;
	}
	else if (*line == '-' || *line == '+' || ft_isdigit(*line))
	{
		*val = ft_atoi(line++);
		while (ft_isdigit(*line))
			line++;
	}
	if (*line == ',')
	{
		line += 3;
		*rgb = hex_atoi(line, 0);
		while (ft_ishex(*line))
			line++;
	}
	else
		*rgb = 0x00FFFFFF;
	while (*line == ' ')
		line++;
	return (line);
}

int	hex_atoi(char *line, int nbr)
{
	if (line && ft_ishex(*line))
	{
		if (ft_isdigit(*line))
			nbr += *line - '0';
		else
			nbr += ft_tolower(*line) - 87;
		if ((line + 1) && ft_ishex(*(line + 1)))
			nbr = hex_atoi(line + 1, nbr * 16);
	}
	return (nbr);
}

void	update_minmax(t_map *map, int value)
{
	if (map->pos == -1)
	{
		map->pos = 0;
		map->min = value;
		map->max = value;
	}
	else if (value < map->min)
		map->min = value;
	else if (value > map->max)
		map->max = value;
}
