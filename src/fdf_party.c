/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_party.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:24:37 by esormune          #+#    #+#             */
/*   Updated: 2021/03/13 10:01:22 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"


/*
** Loops through a rainbow of colours for the background.
*/

void	party_bg(t_map *map)
{
	int	i;

	i = 255;
	while (i >= 0)
	{
		map->bg = (i * 65536) + (i * 256) + i;
		i--;
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
	party_colours(map);
	if (map->view != 0)
		draw_view(map);
	else
		draw_default(map);
}

/*
** Initiates party mode.
*/

void	party_mode(t_map *map)
{
	if (map->party == 0)
		map->party = 1;
	else
		map->party = 0;
}
