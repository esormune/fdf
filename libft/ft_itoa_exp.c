/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:48:16 by esormune          #+#    #+#             */
/*   Updated: 2021/03/02 14:35:20 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static char	*ft_return_zero(long double nb, int prec)
{
	char	buf[100];
	char	*n;
	int		neg;

	neg = 0;
	n = ft_flitoa(0.0, prec);
	if (ft_is_neg((double)nb))
		neg = 1;
	ft_bzero(buf, 100);
	if (neg == 1)
		ft_strcat(buf, "-");
	ft_strcat(buf, n);
	ft_strcat(buf, "e+00");
	free(n);
	return (ft_strdup(buf));
}

static char	*ft_return_exp(char *str, int c, int exp, int neg)
{
	char	buf[100];
	char	*degree;

	ft_bzero(buf, 100);
	degree = ft_itoa(c);
	if (neg == 1)
		ft_strcat(buf, "-");
	ft_strcat(buf, str);
	ft_strcat(buf, "e");
	if (exp == -1)
		ft_strcat(buf, "-");
	if (exp == 1)
		ft_strcat(buf, "+");
	if (c < 10)
	{
		ft_strcat(buf, "0");
		ft_strcat(buf, degree);
	}
	else
		ft_strcat(buf, degree);
	return (ft_strdup(buf));
}

char		*ft_itoa_exp(long double nb, int prec)
{
	char	*str;
	int		count;
	int		exp;
	int		neg;

	count = 0;
	if (nb == 0)
		return (ft_return_zero(nb, prec));
	neg = (nb < 0) ? 1 : 0;
	if (neg == 1)
		nb = nb * (-1);
	exp = (nb < 1) ? -1 : 1;
	while (exp == -1 && nb < 1)
	{
		nb = nb * 10;
		count++;
	}
	while (exp == 1 && nb > 10)
	{
		nb = nb / 10;
		count++;
	}
	str = ft_flitoa_ldouble(nb, prec);
	return (ft_return_exp(str, count, exp, neg));
}
