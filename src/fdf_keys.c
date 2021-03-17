/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:52:12 by esormune          #+#    #+#             */
/*   Updated: 2021/03/17 13:32:46 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Loops background colours for the map.
*/

void	key_background(t_map *map)
{
	int	colours[12] = {BLACK, GREY, WHITE, PINK, MAGENTA,
		RED, PURPLE, BLUE, TURQUOISE, GREEN, YELLOW,
		ORANGE};

	if (map->party != 0)
		return ;
	map->bg_arr++;
	if (map->bg_arr > 12)
		map->bg_arr = 0;
	map->bg = colours[map->bg_arr];
}


/*
** Loops projections for the map.
*/

void	key_projection(t_map *map)
{
	map->view++;
	if (map->view > 4)
		map->view = 0;
}

/*
** Loops colours for the map.
*/

void	key_colour(int key, t_map *map)
{
	int	colours[12] = {WHITE, GREY, BLACK, PINK, MAGENTA,
		RED, PURPLE, BLUE, TURQUOISE, GREEN, YELLOW,
		ORANGE};

	if (key == 99)
	{
		map->colour_arr--;
		if (map->colour_arr < 0)
			map->colour_arr = 11;
		map->colour = colours[map->colour_arr];
	}
	else
	{
		map->colour_arr++;
		if (map->colour_arr >= 12)
			map->colour_arr = 0;
		map->colour = colours[map->colour_arr];
	}
}

/*
** Adjusts zoom.
*/

void	key_zoom(int key, t_map *map)
{
	if (key == 120)
		map->zoom *= 1.05;
	else if (key == 122)
		map->zoom *= 0.95;
}

/*
** Shifts start point of draw.
*/

void	key_move(int key, t_map *map)
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

void	key_z_scale(int key, t_map *map)
{
	if (key == 97)
		map->z_scale *= 0.95;
	else if (key == 115)
		map->z_scale *= 1.05;
/*	if (key == 97)
		map->z_scale -= 0.5;
	if (key == 115)
		map->z_scale += 0.5;*/
}

/*
** Sets the rotation level.
*/

void	key_rotate(int key, t_map *map)
{
	if (key == 44)
		map->rot += 5;
	else
		map->rot -= 5;
}

/*
** Parses the key pressed into its function.
*/

int		fdf_keys(int key, t_map *map)
{
//	printf("%d\n", key);
	if (key == 65361 || key == 65362 || key == 65363 || key == 65364)
		key_move(key, map);
	else if (key == 120 || key == 122)
		key_zoom(key, map);
	else if (key == 97 || key == 115)
		key_z_scale(key, map);
	else if (key == 99 || key == 118)
		key_colour(key, map);
	else if (key == 65289)
		key_projection(map);
	else if (key == 98)
		key_background(map);
	else if (key == 114)
		map_reset(map);
	else if (key == 112)
		party_mode(map);
	else if (key == 44 || key == 46)
		key_rotate(key, map);
	return (0);
}
