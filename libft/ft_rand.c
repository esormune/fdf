/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:57:53 by esormune          #+#    #+#             */
/*   Updated: 2021/03/16 13:40:16 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int	ft_rand(intmax_t ptr, int lim)
{
	if (ptr < 0)
		ptr *= (-1);
	if (ptr % 2 == 0)
		ptr /= 2;
	if (ptr % 3 == 0 && ptr > 100000)
		ptr -= 100000;
	return (ptr % lim);
}