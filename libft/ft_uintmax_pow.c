/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmax_pow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:30:11 by esormune          #+#    #+#             */
/*   Updated: 2021/03/01 19:31:50 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

uintmax_t	ft_uintmax_pow(uintmax_t nb, int pow)
{
	int			i;
	uintmax_t	res;

	if (pow == 0)
		return (1);
	i = pow;
	res = nb;
	while (i > 1)
	{
		res = res * nb;
		i--;
	}
	return (res);
}
