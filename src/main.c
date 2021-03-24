/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:36:26 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 18:34:19 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		die(char *reason)
{
	ft_putendl(reason);
	return (0);
}

char	*die_null(char *reason)
{
	ft_putendl(reason);
	return (NULL);
}

t_coord	**die_struct(char *reason)
{
	ft_putendl(reason);
	return (NULL);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		y;
	t_map	*map;

	if (argc != 2)
		return (die("Usage: ./fdf map_to_open"));
	else if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (die("Open error."));
		if ((y = valid_map(fd)) == 0)
			return (die("Invalid map."));
		else
		{
			close(fd);
			if (((fd = open(argv[1], O_RDONLY)) < 0))
				return (die("Open error."));
			if (!(map = map_init(fd, y)))
				return (die("Error initialising map."));
			close(fd);
			fdf_init(map);
		}
	}
	return (0);
}
