/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:42:04 by esormune          #+#    #+#             */
/*   Updated: 2021/03/16 12:36:27 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Resets map to original status.
*/

void	map_reset(t_map *map)
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
	map->x_start = WIN_HALF - (map->max_width / 2 * map->zoom);
	map->y_start = WIN_HALF - (map->y_size / 2 * map->zoom);
	map->z_start = 0;
	map->rot = 0;
	map->party_scale = 0;
}

/*
** Checks max width for x of map.
*/

int		map_max_width(t_map *map)
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
** Prints the t_coord struct.
*/

void	map_tcoord_print(t_coord coord)
{
	printf("z:%.f x:%.f y:%.f len %d\n", coord.z, coord.x, coord.y, coord.row_len);
}

/*
** Checks map validity. Returns 0 on failure, size of y otherwise.
*/

int			map_valid(int fd)
{
	char	*f;
	size_t	i;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while ((x = get_next_line(fd, &f)) != 0)
	{
		i = 0;
		if (x < 0)
			return (die("Open error."));
		while (f[i] != '\0')
		{
			if (!ft_isdigit(f[i]) && f[i] != '-' && f[i] != ' ')
				return (0);
			i++;
		}
		free(f);
		y++;
	}
	return (y);
}

/*
** Counts number of elements, separated by space, in a string.
*/

static int	map_elem_count(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == ' ')
			i++;
		if (str[i] != '\0' && str[i] != ' ')
		{
			count++;
			while (str[i] != '\0' && str[i] != ' ')
				i++;
		}
	}
	return (count);
}

/*
** Parses the string into the t_coord structs.
*/

static t_coord	*map_parse(char *str, int y)
{
	t_coord	*coord;
	int		count;
	int		x;

	x = 0;
	count = map_elem_count(str);
	if (!(coord = ft_calloc(count, sizeof(t_coord))))
		return (NULL);
	while (x < count && *str != '\0')
	{
		while (*str != '\0' && *str == ' ')
			str++;
		if (*str == '-' || ft_isdigit(*str))
		{
			coord[x].z = (float)ft_atoi(&(*str));
			coord[x].x = x;
			coord[x].y = y;
			coord[x].row_len = count;
			str++;
			if (*str != '\0')
				str = ft_strchr(&(*str), ' ');
//			map_tcoord_print(coord[x]);
			x++;
		}
	}
	return (coord);
}

/*
** Saves map from file into an array of xyz(t_coord) structs.
** Keeps the y size of array into the original t_map struct.
*/

static t_coord	**map_read(int fd, int size, t_map *orig)
{
	t_coord	**map;
	char	*f;
	int		n;
	int		y;

	y = 0;
	if (!(map = (t_coord **)malloc(sizeof(t_coord*) * size)))
		return (NULL);
	while ((n = get_next_line(fd, &f)) != 0)
	{
		if (n < 0)
		{
			//add error message
			return (NULL);
		}
		map[y] = map_parse(f, y);
		y++;
		free(f);
	}
	orig->y_size = y;
	return (map);
	
}

/*
** Allocates space to t_map. Gathers all necessary data through
** helper functions.
*/

t_map			*map_init(int fd, int size)
{
	t_map	*map;
	int		i;

	i = 0;
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->coord = map_read(fd, size, map);
	map->max_width = map_max_width(map);
	map_reset(map);
	party_init(map);
	return (map);
}
