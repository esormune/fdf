/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:30:21 by esormune          #+#    #+#             */
/*   Updated: 2021/03/13 10:10:35 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Resets the image to the background colour.
*/

void	ft_reset_img(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < WIN_MAX)
	{
		map->img[i] = map->bg;
		i++;
	}
}

/*
** A function that multiplies the values with scale and zoom.
*/

static void	draw_scale(t_map *map, t_coord *start, t_coord *end)
{
	start->x = start->x * map->scale * map->zoom + map->x_start;
	start->y = start->y * map->scale * map->zoom + map->y_start;
	start->z = start->z * map->scale * map->zoom + map->z_start;
	end->x = end->x * map->scale * map->zoom + map->x_start;
	end->y = end->y * map->scale * map->zoom + map->y_start;
	end->z = end->z * map->scale * map->zoom + map->z_start;
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
	intmax_t	pixel;

	i = 0;
	draw_scale(map, &start, &end);
	dx = (end.x - start.x);
	dy = (end.y - start.y);
	if (ft_abs(dx) >= ft_abs(dy))
		step = ft_abs(dx);
	else
		step = ft_abs(dy);
	dx = dx / step;
	dy = dy / step;
	while (i <= step)
	{
		pixel = -1;
		if (start.x <= WIN_X && start.x >= 0)
			pixel = (int)start.x + (int)start.y * map->size_line;
		if (pixel <= WIN_MAX && pixel >= 0)
			map->img[pixel] = map->colour;
		start.x += dx;
		start.y += dy;
		i++;
	}
}

/*
** Creates the image of a top-down map.
*/

void	draw_default(t_map *map)
{
	int		i;
	int		j;
	int		count;

	j = 0;
	while (j < map->y_size)
	{
		i = 0;
		count = map->coord[j][i].row_len;
		while (i < count)
		{
			if (i + 1 < count)
				draw_line(map, map->coord[j][i], map->coord[j][i + 1]);
			if (j + 1 < map->y_size)
				draw_line(map, map->coord[j][i], map->coord[j + 1][i]);
			i++;
		}
		j++;
	}
}

/*
** Creates the image of a different projection.
*/

void	draw_view(t_map *map)
{
	int		i;
	int		j;
	int		count;
	t_coord	start;
	t_coord	end;

	j = 0;
	while (j < map->y_size)
	{
		i = 0;
		count = map->coord[j][i].row_len;
		while (i < count)
		{
			if (i + 1 < count)
			{
				start = map->coord[j][i];
				end = map->coord[j][i + 1];
				morph(&start.x, &start.y, (map->coord[j][i].z * map->z_scale), map->view);
				morph(&end.x, &end.y, (map->coord[j][i + 1].z * map->z_scale), map->view);
				draw_line(map, start, end);
			}
			if (j + 1 < map->y_size)
			{
				start = map->coord[j][i];
				end = map->coord[j + 1][i];
				morph(&start.x, &start.y, (map->coord[j][i].z * map->z_scale), map->view);
				morph(&end.x, &end.y, (map->coord[j + 1][i].z * map->z_scale), map->view);
				draw_line(map, start, end);
			}
			i++;
		}
		j++;
	}
}

/*
** Loops through all the coordinates to draw a finished map.
*/

int		draw_map(t_map *map)
{
	if (map->party == 1)
		party_start(map);
	else
	{
		if (map->view != 0)
			draw_view(map);
		else
			draw_default(map);
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
	ft_reset_img(map);
	return (0);
}

/*
int	draw_map(t_map *map)
{
	int		i;
	int		j;
	int		count;

	j = 0;
	while (j < map->y_size)
	{
		i = 0;
		count = map->coord[j][i].row_len;
		while (i < count)
		{
			if (i + 1 < count)
				draw_line(map, map->coord[j][i], map->coord[j][i + 1]);
			if (j + 1 < map->y_size)
				draw_line(map, map->coord[j][i], map->coord[j + 1][i]);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
	ft_bzero(map->img, WIN_MAX * 4);
	return (0);
}
*/
