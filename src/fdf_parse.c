/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:14:14 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 16:28:25 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Counts number of elements, separated by space, in a string.
*/

static int		parse_elem_count(char *str)
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
** Assigns values to a coordinate.
*/

static void		parse_assign(t_coord *coord, int x, int y, int count)
{
	coord->x = x;
	coord->y = y;
	coord->z_orig = coord->z;
	coord->row_len = count;
}

/*
** Parses the string into the t_coord structs.
*/

static t_coord	*parse_coord(char *str, int y)
{
	t_coord	*coord;
	int		count;
	int		x;

	x = 0;
	count = parse_elem_count(str);
	if (!(coord = ft_calloc(count, sizeof(t_coord))))
		return (NULL);
	while (x < count && *str != '\0')
	{
		while (*str != '\0' && *str == ' ')
			str++;
		if (*str == '-' || ft_isdigit(*str))
		{
			coord[x].z = (float)ft_atoi(&(*str));
			parse_assign(&(coord[x]), x, y, count);
			str++;
			if (*str != '\0')
				str = ft_strchr(&(*str), ' ');
			x++;
		}
	}
	return (coord);
}

/*
** Saves map from file into an array of xyz(t_coord) structs.
** Keeps the y size of array into the original t_map struct.
*/

t_coord			**parse_map(int fd, int size, t_map *orig)
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
			return (die_struct("Read error."));
		if (!(map[y] = parse_coord(f, y)))
		{
			free(f);
			free_tcoord_array(map);
			return (die_struct("Malloc error."));
		}
		y++;
		free(f);
	}
	orig->y_size = y;
	return (map);
}
