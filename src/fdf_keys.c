/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:52:12 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 18:43:41 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Parses the key pressed into its triggered event.
*/

int		fdf_keys(int key, t_map *map)
{
	if (key == 65361 || key == 65362 || key == 65363 || key == 65364)
		event_move(key, map);
	else if (key == 120 || key == 122)
		event_zoom(key, map);
	else if (key == 97 || key == 115)
		event_z_scale(key, map);
	else if (key == 99 || key == 118)
		colour_map(key, map);
	else if (key == 65289)
		event_projection(map);
	else if (key == 98)
		colour_background(map);
	else if (key == 114)
		reset_map(map);
	else if (key == 112)
		party_mode(map);
	else if (key == 44 || key == 46)
		event_rotate(key, map);
	else if (key == 100)
		depth_key(map);
	else if (key == 65307)
		fdf_exit(map);
	map->draw = 0;
	return (0);
}
