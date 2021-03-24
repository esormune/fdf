/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:30:21 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 17:37:49 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Returns step for draw_line function.
*/

float		draw_step(float dx, float dy)
{
	if (ft_abs(dx) >= ft_abs(dy))
		return (ft_abs(dx));
	else
		return (ft_abs(dy));
}

/*
** Takes two coordinates and then uses the dda algorithm to draw a line.
*/

static void	draw_line(t_map *map, t_coord start, t_coord end)
{
	float		dx;
	float		dy;
	float		step;
	int			i;
	uintmax_t	pixel;

	i = 0;
	morph_scale(map, &start, &end);
	dx = (end.x - start.x);
	dy = (end.y - start.y);
	step = draw_step(dx, dy);
	dx = dx / step;
	dy = dy / step;
	while (i <= step)
	{
		pixel = -1;
		if ((int)start.x < WIN_X && (int)start.x >= 0)
			pixel = (int)start.x + (int)start.y * map->size_line;
		if (pixel <= WIN_MAX && pixel >= 0)
			map->img[pixel] = map->colour;
		start.x += dx;
		start.y += dy;
		i++;
	}
}

/*
** Transforms the coordinates given into ones to be drawn. Calls draw function.
** s and e refer to start and end. c refers to center.
*/

static void	draw_transform(t_coord s, t_coord e, t_coord c, t_map *map)
{
	t_coord	start;
	t_coord	end;

	start = s;
	end = e;
	if (map->rot != 0)
	{
		morph_rotate(&start, c, map->rot);
		morph_rotate(&end, c, map->rot);
	}
	morph_view(&start.x, &start.y, (s.z * map->z_scale), map->view);
	morph_view(&end.x, &end.y, (e.z * map->z_scale), map->view);
	if (map->depth == 0)
		draw_line(map, start, end);
	else if (map->depth == 1)
		depth_draw_line(map, start, end);
}

/*
** Creates the image of the map by looping through all the points.
*/

void		draw_create(t_map *map)
{
	int		i;
	int		j;
	int		count;
	t_coord	center;

	j = 0;
	center.x = map->max_width / 2;
	center.y = map->y_size / 2;
	while (j < map->y_size)
	{
		i = 0;
		count = map->coord[j][i].row_len;
		while (i < count)
		{
			if (i + 1 < count)
				draw_transform(map->coord[j][i], map->coord[j][i + 1],
					center, map);
			if ((j + 1 < map->y_size) && (map->coord[j + 1][i].row_len > i))
				draw_transform(map->coord[j][i], map->coord[j + 1][i],
					center, map);
			i++;
		}
		j++;
	}
	map->draw = 1;
}

/*
** Loops through all the coordinates to draw a finished map.
*/

int			draw_map(t_map *map)
{
	if (map->draw != 1 && map->party == 0)
	{
		reset_img(map, map->bg);
		draw_create(map);
		mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
		text_put(map);
	}
	else if (map->party != 0)
	{
		reset_img(map, map->bg);
		party_start(map);
		mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
	}
	return (0);
}
