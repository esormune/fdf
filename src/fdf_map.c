/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:42:04 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 16:27:59 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Checks max width for x of map.
*/

int			map_max_width(t_map *map)
{
	int		max;
	int		i;

	max = map->coord[0][0].row_len;
	i = 1;
	while (i < map->y_size)
	{
		max = ft_max(max, map->coord[i][0].row_len);
		i++;
	}
	return (max);
}

/*
** Sets the colour of coordinates for the depth view. Based on z size and
** max size; z at 0 is white, max z is red, min z is blue.
*/

static void	map_coord_colours(t_map *map)
{
	int		i;
	int		j;
	int		x_len;

	j = 0;
	while (j < map->y_size)
	{
		i = 0;
		x_len = map->coord[j][i].row_len;
		while (i < x_len)
		{
			if (map->coord[j][i].z == 0)
			{
				map->coord[j][i].r = 255;
				map->coord[j][i].g = 255;
				map->coord[j][i].b = 255;
				map->coord[j][i].colour = WHITE;
			}
			else
				map->coord[j][i].colour = colour_get(&map->coord[j][i], map);
			i++;
		}
		j++;
	}
}

/*
** Loops through all the coordinates to find out the minimum
** and maximum value of z. This function also sets the rgb of coords to 0.
*/

void		map_set_depth(t_map *map)
{
	int		i;
	int		j;
	int		x_len;

	j = 0;
	map->min_z = map->coord[0][0].z;
	map->max_z = map->coord[0][0].z;
	while (j < map->y_size)
	{
		i = 0;
		x_len = map->coord[j][i].row_len;
		while (i < x_len)
		{
			map->coord[j][i].r = 0;
			map->coord[j][i].g = 0;
			map->coord[j][i].b = 0;
			map->min_z = ft_min(map->min_z, map->coord[j][i].z);
			map->max_z = ft_max(map->max_z, map->coord[j][i].z);
			i++;
		}
		j++;
	}
}

/*
** Allocates space to t_map. Gathers all necessary data through
** helper functions.
*/

t_map		*map_init(int fd, int size)
{
	t_map	*map;
	int		i;
	int		max;

	i = 0;
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	if (!(map->coord = parse_map(fd, size, map)))
		return (NULL);
	map->max_width = map_max_width(map);
	max = ft_max(map->max_width, map->y_size);
	map->zoom = WIN_X / (max + 10);
	map->x_start_orig = WIN_HALF - (map->max_width / 2 * map->zoom);
	map->y_start_orig = WIN_HALF - (map->y_size / 2 * map->zoom);
	reset_map(map);
	map_set_depth(map);
	map_coord_colours(map);
	party_init(map);
	return (map);
}
