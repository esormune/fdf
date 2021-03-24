/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:36:27 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 17:02:16 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Returns the colour for the dancefloor based on sleep timer. For the striped
** floor in party mode 2, this function is entered into line by line, thereby
** creating the striped effect. For the regular dancefloor, it is only entered
** into after one square has been drawn.
*/

int		floor_colour(t_map *map, int i)
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

void	floor_transform(t_coord s, t_coord e, t_map *map, int i)
{
	t_coord	start;
	t_coord	end;

	start = s;
	end = e;
	morph_view(&start.x, &start.y, 1, map->view);
	morph_view(&end.x, &end.y, 1, map->view);
	if (map->party == 2)
		square_draw(map, start, end, floor_colour(map, i));
	else
		square_draw(map, start, end, i);
}

/*
** Creates a crazy striped dancefloor.
*/

void	floor_stripe(t_map *map)
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
			floor_transform(temp_s, temp_e, map, j);
			temp_s.y++;
			temp_e.y++;
			i++;
		}
		j++;
	}
}

/*
** Creates a dancefloor. Colour is stored in temp_s.colour to save variables.
*/

void	floor_create(t_map *map)
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
		temp_s.colour = floor_colour(map, j);
		while (i < y_size)
		{
			floor_transform(temp_s, temp_e, map, temp_s.colour);
			temp_s.y++;
			temp_e.y++;
			i++;
		}
		j++;
	}
}
