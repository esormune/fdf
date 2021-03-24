/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:54:39 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 17:04:40 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** A function that centers the squares of the dancefloor for views 1 and 4.
*/

static void	square_center(t_coord *start, t_coord *end, t_map *map)
{
	if (map->view == 1)
	{
		start->x += WIN_HALF;
		start->y = start->y - SQ_SIZE + map->y_start_orig;
		end->x += WIN_HALF;
		end->y += end->y - SQ_SIZE + map->y_start_orig;
	}
	else if (map->view == 4)
	{
		start->x -= SQ_SIZE;
		start->y += SQ_SIZE + map->y_start_orig;
		end->x -= SQ_SIZE;
		end->y += SQ_SIZE + map->y_start_orig;
	}
}

/*
** Draw line for squares. Doesn't scale.
*/

void		square_draw(t_map *map, t_coord start, t_coord end, int colour)
{
	float		dx;
	float		dy;
	float		step;
	int			i;
	uintmax_t	pixel;

	i = 0;
	dx = (end.x - start.x);
	dy = (end.y - start.y);
	if (map->view == 1 || map->view == 4)
		square_center(&start, &end, map);
	step = draw_step(dx, dy);
	dx = dx / step;
	dy = dy / step;
	while (i <= step)
	{
		pixel = -1;
		if ((int)start.x < WIN_X && (int)start.x >= 0)
			pixel = (int)start.x + (int)start.y * map->size_line;
		if (pixel <= WIN_MAX && pixel >= 0)
			map->img[pixel] = colour;
		start.x += dx;
		start.y += dy;
		i++;
	}
}
