/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:54:09 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/04 14:54:10 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		sub = ft_calloc(1, 1);
		if (!sub)
			return (NULL);
	}
	else
	{
		i = ft_strlen(s + start);
		if (i > len)
			i = len;
		sub = malloc(i + 1);
		if (!sub)
			return (NULL);
		sub[i] = 0;
		while (i-- > 0)
			sub[i] = s[start + i];
	}
	return (sub);
}
