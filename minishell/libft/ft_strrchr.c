/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:54:00 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/04 14:54:00 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			p = (char *)(s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		p = (char *)(s + i);
	return (p);
}
