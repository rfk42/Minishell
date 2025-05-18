/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:49:10 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/04 14:49:11 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(long nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		len++;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nl;
	char	*result;

	len = nbr_len(n);
	nl = n;
	if (n < 0)
		nl = -nl;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = 0;
	if (nl == 0)
		result[0] = '0';
	else
	{
		while (nl)
		{
			result[--len] = nl % 10 + '0';
			nl = (nl - (nl % 10)) / 10;
		}
		if (n < 0)
			result[0] = '-';
	}
	return (result);
}
