/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:56:03 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 15:58:41 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Resets the image to the given colour.
*/

void	reset_img(t_map *map, int colour)
{
	size_t	i;

	i = 0;
	while (i < WIN_MAX)
	{
		map->img[i] = colour;
		i++;
	}
}

/*
** Resets map to original status.
*/

void	reset_map(t_map *map)
{
	int	max;

	max = ft_max(map->max_width, map->y_size);
	map->z_scale = 1;
	map->zoom = WIN_X / (max + 10);
	map->view = 0;
	map->colour = WHITE;
	map->colour_arr = 0;
	map->bg = BLACK;
	map->bg_arr = 0;
	map->party = 0;
	map->r = 255;
	map->g = 0;
	map->b = 0;
	map->x_start = map->x_start_orig;
	map->y_start = map->y_start_orig;
	map->z_start = 0;
	map->rot = 0;
	map->party_scale = 0;
	map->depth = 0;
	map->draw = 0;
	map->i = 0;
}
