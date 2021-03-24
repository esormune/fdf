/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:46:22 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 15:47:02 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Loops projections for the map.
*/

void	event_projection(t_map *map)
{
	map->view++;
	if (map->view > 4)
		map->view = 0;
}

/*
** Adjusts zoom.
*/

void	event_zoom(int key, t_map *map)
{
	if (key == 120)
		map->zoom *= 1.05;
	else if (key == 122)
		map->zoom *= 0.95;
}

/*
** Shifts start point of draw.
*/

void	event_move(int key, t_map *map)
{
	if (key == 65361)
		map->x_start -= 5;
	else if (key == 65362)
		map->y_start -= 5;
	else if (key == 65363)
		map->x_start += 5;
	else if (key == 65364)
		map->y_start += 5;
}

/*
** Scales the z value of map.
*/

void	event_z_scale(int key, t_map *map)
{
	if (key == 97)
		map->z_scale *= 0.95;
	else if (key == 115)
		map->z_scale *= 1.05;
}

/*
** Sets the rotation level.
*/

void	event_rotate(int key, t_map *map)
{
	if (key == 44)
		map->rot += 5;
	else
		map->rot -= 5;
}
