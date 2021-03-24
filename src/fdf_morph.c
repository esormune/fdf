/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_morph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:44:18 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 15:19:16 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Sets the points for conversion.
*/

void	morph_view(float *x, float *y, float z, int i)
{
	float	temp_x;
	float	temp_y;

	temp_x = *x;
	temp_y = *y;
	if (i == 1)
	{
		*x = (temp_x - temp_y) * cos(0.523599);
		*y = -z + (temp_x + temp_y) * sin(0.523599);
	}
	else if (i == 2)
	{
		*x = temp_x + (z / 2);
		*y = temp_y + (-z / 4);
	}
	else if (i == 3)
	{
		*x = temp_x * cos(0.122173) + ((z * cos(0.733038)) / 2);
		*y = temp_y + ((z * sin(0.733038) / 2) - temp_x * sin(0.122173));
	}
	else if (i == 4)
	{
		*x = temp_x + 0.5 * temp_y * cos(0.698132);
		*y = -z + 0.5 * temp_y * sin(0.698132);
	}
}

/*
** Rotates the points on a map.
*/

void	morph_rotate(t_coord *p, t_coord center, float angle)
{
	float	temp_x;
	float	temp_y;
	float	s;
	float	c;
	float	rotation_angle;

	rotation_angle = angle * M_PI / 180;
	s = sin(rotation_angle);
	c = cos(rotation_angle);
	p->x -= center.x;
	p->y -= center.y;
	temp_x = p->x * c - p->y * s;
	temp_y = p->x * s + p->y * c;
	p->x = temp_x + center.x;
	p->y = temp_y + center.y;
}

/*
** Scales the points to fit the required zoom.
*/

void	morph_scale(t_map *map, t_coord *start, t_coord *end)
{
	start->x = start->x * map->zoom + map->x_start;
	start->y = start->y * map->zoom + map->y_start;
	start->z = start->z * map->zoom + map->z_start;
	end->x = end->x * map->zoom + map->x_start;
	end->y = end->y * map->zoom + map->y_start;
	end->z = end->z * map->zoom + map->z_start;
}
