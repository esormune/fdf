/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:39:23 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 16:28:33 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Frees the t_coord structs in the array in the case of a malloc error.
*/

void	free_tcoord_array(t_coord **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
** Function that maybe frees memory and exits the programme.
*/

int		fdf_exit(t_map *map)
{
	mlx_destroy_image(map->mlx_ptr, map->img_ptr);
	exit(0);
}

/*
** Initialises window. Begins looping.
*/

int		fdf_init(t_map *map)
{
	map->mlx_ptr = mlx_init();
	if (map->mlx_ptr == NULL)
		return (die("Error opening window."));
	map->win_ptr = mlx_new_window(map->mlx_ptr, WIN_X, WIN_Y, "Fdf");
	map->img_ptr = mlx_new_image(map->mlx_ptr, WIN_X, WIN_Y);
	map->img = NULL;
	map->img = (int *)mlx_get_data_addr(map->img_ptr, &map->bpp,
		&map->size_line, &map->endian);
	map->size_line /= 4;
	mlx_hook(map->win_ptr, 33, 0, fdf_exit, map);
	mlx_hook(map->win_ptr, 2, (long)1L, fdf_keys, map);
	mlx_loop_hook(map->mlx_ptr, draw_map, map);
	mlx_loop(map->mlx_ptr);
	return (0);
}
