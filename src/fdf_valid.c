/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:06:07 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 16:06:46 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Checks map validity. Returns 0 on failure, size of y otherwise.
*/

int	valid_map(int fd)
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
