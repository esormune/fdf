/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_party.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:24:37 by esormune          #+#    #+#             */
/*   Updated: 2021/03/17 13:31:14 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Resizes the z-scale to go bigger and smaller.
*/

void	party_scale(t_map *map)
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
** Returns a random colour. Used for the dance floor.
*/

int		party_bg(int start)
{
	int		ret;

	ret = ft_rand((intmax_t)start, WHITE);
	return (ret);
}

/*
** Colours a singular square. "End" gains the values of "start" for the sake of
** reducing variables.
*/

void	party_square(t_map *map, int colour, t_coord start, t_coord end)
{
	size_t		x_size;
	size_t		y_size;
	intmax_t	pixel;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	x_size = end.x - start.x;
	y_size = end.y - start.y;
	end = start;
	while (j < y_size)
	{
		i = 0;
		end.x = start.x;
		while (i < x_size)
		{
			pixel = -1;
			if ((int)end.x < WIN_X && (int)end.x >= 0)
				pixel = (int)end.x + (int)end.y * map->size_line;
			if (pixel <= WIN_MAX && pixel >= 0)
				map->img[pixel] = colour;
			end.x++;
			i++;
		}
		end.y++;
		j++;
	}
}

/*
** Makes the dancefloor for party mode.
*/

void	party_floor(t_map *map)
{
	int		i;

	i = 0;
	while (i < WIN_MAX)
		map->img[i++] = BLACK;
	i = 0;
	while (i < SQUARES)
	{
		map->tiles[i].inc++;
		if (map->tiles[i].inc >= map->tiles[i].sleep)
		{
			map->tiles[i].inc = 0;
			if (map->tiles[i].black == 1)
				map->tiles[i].black = 0;
			else
				map->tiles[i].black = 1;
			map->tiles[i].colour += map->tiles[i].change;
			if (map->tiles[i].colour > WHITE)
				map->tiles[i].colour = 0;
		}
		if (map->tiles[i].black == 1)
			party_square(map, BLACK, map->tiles[i].start, map->tiles[i].end);
		else
			party_square(map, map->tiles[i].colour, map->tiles[i].start,
				map->tiles[i].end);
		i++;
	}
}

/*
** Loops through a rainbow of colours for the map.
*/

void	party_colours(t_map *map)
{
	if (map->r == 255 && map->g == 0 && map->b < 255)
		map->b += 5;
	else if (map->b == 255 && map->g == 0 && map->r > 0)
		map->r -= 5;
	else if (map->r == 0 && map->b == 255 && map->g < 255)
		map->g += 5;
	else if (map->g == 255 && map-> r == 0 && map->b > 0)
		map->b -= 5;
	else if (map->g == 255 && map->b == 0 && map->r < 255)
		map->r += 5;
	else if (map->r == 255 && map->b == 0 && map->g > 0)
		map->g -= 5;
	map->colour = (map->r * 65536) + (map->g * 256) + map->b;
}

/*
** Contains all the necessary functions for the party event.
*/

void	party_start(t_map *map)
{
	reset_img(map, BLACK);
	party_colours(map);
	map->rot += 5;
	party_scale(map);
//	party_floor(map);
	if (map->party == 2)
		party_stripe_floor(map);
	else
		party_create_floor(map);
	draw_create(map);
}

/*
** Initiates party mode.
*/

void	party_mode(t_map *map)
{
	int	max;

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
** Initialises the dance floor of map so that all structs of t_floor have a random
** start value, a random sleep time, a random colour, and a random scale (change)
** with which the colour with increment.
*/

void	party_init(t_map *map)
{
	int	colours[16] = {BLACK, GREY, WHITE, PINK, MAGENTA,
		RED, PURPLE, BLUE, TURQUOISE, GREEN, YELLOW,
		ORANGE, GREEN, YELLOW, RED, TURQUOISE};
	int	i;
	int	ptr;

	i = 0;
	while (i < SQUARES)
	{
		ptr = (int)(&map->tiles[i]);
		if (i < 16)
			map->tiles[i].colour = colours[i];
		else
			map->tiles[i].colour = colours[ptr % 12];
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
		if (i % 2 == 0 || i % 5 == 0)
			map->tiles[i].black = 0;
		else
			map->tiles[i].black = 1;
//		printf("tile[%d] colour %d\n", i, map->tiles[i].colour);
		i++;
	}
}

/*
** Draw line for squares. Doesn't scale.
*/

static void	draw_square(t_map *map, t_coord start, t_coord end, int colour)
{
	float		dx;
	float		dy;
	float		step;
	int			i;
	uintmax_t	pixel;

	i = 0;
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
		if ((int)start.x < WIN_X && (int)start.x >= 0)
			pixel = (int)start.x + (int)start.y * map->size_line;
		if (pixel <= WIN_MAX && pixel >= 0)
			map->img[pixel] = colour;
		start.x += dx;
		start.y += dy;
		i++;
	}
}

/*
** Returns the colour for the square based on sleep timer.
*/

int		party_sq_colour(t_map *map, int i)
{
	map->tiles[i].inc++;
	if (map->tiles[i].inc >= map->tiles[i].sleep)
	{
		map->tiles[i].inc = 0;
		if (map->tiles[i].black == 1)
			map->tiles[i].black = 0;
		else
			map->tiles[i].black = 1;
		map->tiles[i].colour += map->tiles[i].change;
		if (map->tiles[i].colour > WHITE)
			map->tiles[i].colour = 0;
	}
	if (map->tiles[i].black == 1)
		return (BLACK);
	else
		return (map->tiles[i].colour);
}
/*
** Transforms the dancefloor into an isometric view. The int i is a colour
** if coming in regular view. If the striped view is chosen, it is
** a placemarker for the colour function.
*/

void	party_transform_floor(t_coord s, t_coord e, t_map *map, int i)
{
	t_coord	start;
	t_coord	end;

	start = s;
	end = e;
	morph_view(&start.x, &start.y, 1, map->view);
	morph_view(&end.x, &end.y, 1, map->view);
	if (map->party == 2)
		draw_square(map, start, end, party_sq_colour(map, i));
	else
		draw_square(map, start, end, i);
}

/*
** Creates a crazy striped dancefloor.
*/

void	party_stripe_floor(t_map *map)
{
	int		i;
	int		j;
	int		y_size;
	t_coord	temp_s;
	t_coord	temp_e;

	j = 0;
	y_size = map->tiles[0].end.y - map->tiles[0].start.y;
	while (j < SQUARES)
	{
		i = 0;
		temp_s = map->tiles[j].start;
		temp_e = map->tiles[j].end;
		temp_e.y = map->tiles[j].start.y;
		while (i < y_size)
		{
			party_transform_floor(temp_s, temp_e, map, j);
			temp_s.y++;
			temp_e.y++;
			i++;
		}
		j++;
	}
}


/*
** Creates a dancefloor.
*/

void	party_create_floor(t_map *map)
{
	int		i;
	int		j;
	int		y_size;
	int		colour;
	t_coord	temp_s;
	t_coord	temp_e;

	j = 0;
	y_size = map->tiles[0].end.y - map->tiles[0].start.y;
	while (j < SQUARES)
	{
		i = 0;
		temp_s = map->tiles[j].start;
		temp_e = map->tiles[j].end;
		temp_e.y = map->tiles[j].start.y;
		colour = party_sq_colour(map, j);
		while (i < y_size)
		{
			party_transform_floor(temp_s, temp_e, map, colour);
			temp_s.y++;
			temp_e.y++;
			i++;
		}
		j++;
	}
}
