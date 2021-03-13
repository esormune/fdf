/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:14:17 by esormune          #+#    #+#             */
/*   Updated: 2021/03/04 13:16:40 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	if (!s1 || !s2)
	{
		if (!s1 && !s2)
			return (NULL);
		else if (!s1)
			return (ft_strdup(s2));
		else if (!s2)
			return (ft_strdup(s1));
	}
	len = (ft_strlen((char*)s1) + ft_strlen((char*)s2));
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = (char)*s1++;
	while (*s2 != '\0')
		dest[i++] = (char)*s2++;
	dest[i] = '\0';
	free(s1);
	free(s2);
	return (dest);
}
