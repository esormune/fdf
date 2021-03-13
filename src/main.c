/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:36:26 by esormune          #+#    #+#             */
/*   Updated: 2021/03/09 14:28:30 by esormune         ###   ########.fr       */
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

//add wall wextra werror

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
		if ((y = map_valid(fd)) == 0)
			return (die("Invalid map."));
		else
		{
			close(fd);
			fd = open(argv[1], O_RDONLY);
			if (fd < 0)
				return (die("Open error."));
			if (!(map = map_init(fd, y)))
				return (die("Malloc error."));
			close(fd);
			fdf_init(map);
		}
	}
	return (0);
}
