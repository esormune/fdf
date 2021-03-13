/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_morph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:44:18 by esormune          #+#    #+#             */
/*   Updated: 2021/03/11 21:28:56 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Sets the points for conversion.
*/

void	morph(float *x, float *y, float z, int i)
{
	float	temp_x;
	float	temp_y;

	temp_x = *x;
	temp_y = *y;
	if (i == 1)
	{
		*x = (temp_x - temp_y) * cos(0.523599);
		*y = -z + (temp_x + temp_y) * sin(0.523599);
	}
	else if (i == 2)
	{
		*x = temp_x + (z / 2);
		*y = temp_y + (-z / 4);
	}
	else if (i == 3)
	{
		*x = temp_x * cos(0.122173) + ((z * cos(0.733038)) / 2);
		*y = temp_y + ((z * sin(0.733038) / 2) - temp_x * sin(0.122173));
	}
	else if (i == 4)
	{
		*x = temp_x + 0.5 * temp_y * cos(0.698132);
		*y = -z + 0.5 * temp_y * sin(0.698132);
	}
}

/*
void	morph(float *x, float *y, float z, int i)
{
	float	temp_x;
	float	temp_y;

	temp_x = *x;
	temp_y = *y;
	if (i == 1)
	{
		*x = (temp_x - temp_y) * cos(0.523599);
		*y = -z + (temp_x + temp_y) * sin(0.523599);
	}
	else if (i == 2)
	{
		*x = temp_x + (z / 2);
		*y = temp_y + (-z / 4);
	}
	else if (i == 3)
	{
		*x = temp_x * cos(0.122173) + ((z * cos(0.733038)) / 2);
		*y = temp_y + ((z * sin(0.733038) / 2) - temp_x * sin(0.122173));
	}
	else if (i == 4)
	{
		*x = temp_x + 0.5 * z * cos(0.698132);
		*y = temp_y + 0.5 * z * sin(0.698132);
	}
}
*/
