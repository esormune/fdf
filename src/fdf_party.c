/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_party.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:24:37 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 17:05:05 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Resizes the z-scale to go bigger and smaller.
*/

void		party_scale(t_map *map)
{
	if (map->party_scale >= 0 && map->party_scale < 10)
	{
		map->z_scale *= 1.05;
		map->party_scale++;
		if (map->party_scale == 10)
			map->party_scale = -10;
	}
	else if (map->party_scale < 0 && map->party_scale >= -10)
	{
		map->z_scale /= 1.05;
		map->party_scale++;
	}
}

/*
** Contains all the necessary functions for the party event.
*/

void		party_start(t_map *map)
{
	reset_img(map, BLACK);
	colours_party(map);
	map->rot += 5;
	party_scale(map);
	if (map->party == 2)
		floor_stripe(map);
	else
		floor_create(map);
	draw_create(map);
}

/*
** Initiates party mode.
*/

void		party_mode(t_map *map)
{
	int	max;

	map->depth = 0;
	if (map->party == 0)
		map->party = 1;
	else if (map->party == 1)
		map->party = 2;
	else
	{
		max = ft_max(map->max_width, map->y_size);
		map->party = 0;
		map->colour = WHITE;
		map->rot = 0;
		map->z_scale = 1;
		map->zoom = WIN_X / (max + 10);
		map->bg = BLACK;
	}
}

/*
** Returns an initial colour for the party dance floor based on the i
** position in the provided array.
*/

static int	party_init_colour(int i)
{
	static int	colours[] = {BLACK, GREY, WHITE, PINK, MAGENTA,
				RED, PURPLE, BLUE, TURQUOISE, GREEN, YELLOW,
				ORANGE, GREEN, YELLOW, RED, TURQUOISE};

	if (i < 16)
		return (colours[i]);
	else
		return (colours[i % 12]);
}

/*
** Initialises the dance floor of map so that all structs of t_floor have
** a random start value, a random sleep time, a random colour, and a random
** integer (change) with which the colour with increment.
*/

void		party_init(t_map *map)
{
	int	i;
	int	ptr;

	i = 0;
	while (i < SQUARES)
	{
		ptr = (int)(&map->tiles[i]);
		map->tiles[i].colour = party_init_colour(i);
		map->tiles[i].sleep = ft_rand(ptr, 50);
		if (map->tiles[i].sleep < 10)
			map->tiles[i].sleep += 5;
		map->tiles[i].inc = ft_rand(ptr, 10);
		map->tiles[i].change = ft_rand(ptr, 1000);
		map->tiles[i].start.x = SQ_SIZE * (i % SQ_PR) + 10;
		map->tiles[i].start.y = SQ_SIZE * (i / SQ_PR) + 10;
		map->tiles[i].start.z = 1;
		map->tiles[i].end.x = map->tiles[i].start.x + SQ_SIZE - 20;
		map->tiles[i].end.y = map->tiles[i].start.y + SQ_SIZE - 20;
		map->tiles[i].end.z = 1;
		map->tiles[i].black = 1;
		if (i % 2 == 0 || i % 5 == 0)
			map->tiles[i].black = 0;
		i++;
	}
}
