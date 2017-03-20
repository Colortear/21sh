/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 22:29:00 by wdebs             #+#    #+#             */
/*   Updated: 2016/09/27 14:12:38 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive(long n, int fd)
{
	if (n == 0)
		return ;
	ft_recursive(n / 10, fd);
	n = n % 10;
	ft_putchar_fd(n + '0', fd);
}

void		ft_putnbr_fd(int nbr, int fd)
{
	long lnbr;

	lnbr = nbr;
	if (lnbr < 0)
	{
		ft_putchar_fd('-', fd);
		lnbr *= -1;
	}
	if (lnbr == 0)
		ft_putchar_fd('0', fd);
	if (lnbr > 0)
	{
		ft_recursive(lnbr, fd);
	}
}
