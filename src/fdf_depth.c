/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_depth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:24:03 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 16:14:06 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Triggers depth view or turns it off. Incompatible with oarty mode.
*/

void		depth_key(t_map *map)
{
	if (map->party != 0)
		return ;
	if (map->depth == 0)
		map->depth = 1;
	else
		map->depth = 0;
}

/*
** Calculates colour for a single pixel in depth view.
*/

static int	depth_get_colour(t_coord start, t_coord end, int step, t_map *map)
{
	float	change;
	float	pos;

	pos = (1 - ((float)map->i / step)) * start.z_orig +
		(((float)map->i / step) * end.z_orig);
	if (pos == 0)
		return (WHITE);
	else if (pos < 0)
	{
		change = ft_abs(pos / map->min_z);
		start.r = 255 - (change * 255);
		return (ft_colour(start.r, start.r, 255));
	}
	else
	{
		change = ft_abs(pos / map->max_z);
		start.b = 255 - (change * 255);
		return (ft_colour(255, start.b, start.b));
	}
}

/*
** Line drawing algorithm where the colour is constantly calculated
** for depth view.
*/

void		depth_draw_line(t_map *map, t_coord start, t_coord end)
{
	float		dx;
	float		dy;
	float		step;
	uintmax_t	pixel;

	map->i = 0;
	morph_scale(map, &start, &end);
	dx = (end.x - start.x);
	dy = (end.y - start.y);
	step = draw_step(dx, dy);
	dx = dx / step;
	dy = dy / step;
	while (map->i <= step)
	{
		pixel = -1;
		if ((int)start.x < WIN_X && (int)start.x >= 0)
			pixel = (int)start.x + (int)start.y * map->size_line;
		if (pixel <= WIN_MAX && pixel >= 0)
			map->img[pixel] = depth_get_colour(start, end, step, map);
		start.x += dx;
		start.y += dy;
		map->i++;
	}
}
