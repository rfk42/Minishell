/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:51:17 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/04 14:51:18 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nl;

	nl = n;
	if (nl < 0)
	{
		ft_putchar_fd('-', fd);
		nl = -nl;
	}
	if (nl / 10 > 0)
	{
		ft_putnbr_fd(nl / 10, fd);
		ft_putchar_fd((nl % 10) + '0', fd);
	}
	else
		ft_putchar_fd((nl % 10) + '0', fd);
}
