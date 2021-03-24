/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:30:08 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 17:05:14 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Places the helper text into the image.
*/

void	text_put(t_map *map)
{
	int	colour;

	colour = BLACK;
	if (map->bg == BLACK || map->bg == BLUE)
		colour = WHITE;
	mlx_string_put(map->mlx_ptr, map->win_ptr, 50, 50, colour,
		"Change view: tab");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 50, 70, colour,
		"Scale down/up: A / S");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 50, 90, colour, "Depth view: D");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 50, 110, colour, "Zoom: Z / X");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 50, 130, colour,
		"Change colour: C / V");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 650, 50, colour, "Rotate: < >");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 650, 70, colour,
		"Move: arrow keys");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 650, 90, colour,
		"Change background: B");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 650, 110, colour, "Reset: R");
	mlx_string_put(map->mlx_ptr, map->win_ptr, 650, 130, colour,
		"???: P (Epilepsy TW)");
}
