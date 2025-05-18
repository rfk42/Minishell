/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:51:54 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/04 14:51:55 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s;

	len = ft_strlen(s1);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = 0;
	while (len-- > 0)
		s[len] = s1[len];
	return (s);
}
