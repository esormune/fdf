/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:33:38 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 17:04:24 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Loops through a rainbow of colours for the map.
*/

void		colours_party(t_map *map)
{
	if (map->r == 255 && map->g == 0 && map->b < 255)
		map->b += 5;
	else if (map->b == 255 && map->g == 0 && map->r > 0)
		map->r -= 5;
	else if (map->r == 0 && map->b == 255 && map->g < 255)
		map->g += 5;
	else if (map->g == 255 && map->r == 0 && map->b > 0)
		map->b -= 5;
	else if (map->g == 255 && map->b == 0 && map->r < 255)
		map->r += 5;
	else if (map->r == 255 && map->b == 0 && map->g > 0)
		map->g -= 5;
	map->colour = (map->r * 65536) + (map->g * 256) + map->b;
}

/*
** Returns a colour when the z value is positive based on the value's
** position on the whole z range.
*/

static int	colour_pos(t_coord *p, t_map *map)
{
	int		diff;
	float	ratio;

	p->r = 255;
	diff = map->max_z - p->z;
	if (diff != 0)
	{
		ratio = (ft_abs(map->max_z)) / diff;
		if (ratio != 0)
		{
			p->b = 255 / ratio;
			p->g = 255 / ratio;
		}
	}
	return (ft_colour(p->r, p->g, p->b));
}

/*
** Gets and returns the colour for the coordinates based on their z value
** and that value's position on the whole z range. Negative z values are
** assigned here, positive ones in a nearly identical helper function for
** the sake of space.
*/

int			colour_get(t_coord *p, t_map *map)
{
	int		diff;
	float	ratio;

	if (p->z < 0)
	{
		p->b = 255;
		diff = p->z - map->min_z;
		if (diff != 0)
		{
			ratio = (ft_abs(map->min_z)) / diff;
			if (ratio != 0)
			{
				p->r = 255 / ratio;
				p->g = 255 / ratio;
			}
		}
	}
	else if (p->z > 0)
	{
		return (colour_pos(p, map));
	}
	return (ft_colour(p->r, p->g, p->b));
}

/*
** Loops colours for the map.
*/

void		colour_map(int key, t_map *map)
{
	static int	colours[12] = {WHITE, GREY, BLACK, PINK, MAGENTA,
		RED, PURPLE, BLUE, TURQUOISE, GREEN, YELLOW,
		ORANGE};

	if (key == 99)
	{
		map->colour_arr--;
		if (map->colour_arr < 0)
			map->colour_arr = 11;
		map->colour = colours[map->colour_arr];
	}
	else
	{
		map->colour_arr++;
		if (map->colour_arr >= 12)
			map->colour_arr = 0;
		map->colour = colours[map->colour_arr];
	}
}

/*
** Loops background colours for the map.
*/

void		colour_background(t_map *map)
{
	static int	colours[12] = {BLACK, GREY, WHITE, PINK, MAGENTA,
		RED, PURPLE, BLUE, TURQUOISE, GREEN, YELLOW,
		ORANGE};

	if (map->party != 0)
		return ;
	map->bg_arr++;
	if (map->bg_arr > 12)
		map->bg_arr = 0;
	map->bg = colours[map->bg_arr];
}
