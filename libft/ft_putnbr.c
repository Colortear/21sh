/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 17:43:00 by wdebs             #+#    #+#             */
/*   Updated: 2016/09/26 21:05:38 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive(long n)
{
	if (n == 0)
		return ;
	ft_recursive(n / 10);
	n = n % 10;
	ft_putchar(n + '0');
}

void		ft_putnbr(int nbr)
{
	long lnbr;

	lnbr = nbr;
	if (lnbr < 0)
	{
		ft_putchar('-');
		lnbr *= -1;
	}
	if (lnbr == 0)
		ft_putchar('0');
	if (lnbr > 0)
	{
		ft_recursive(lnbr);
	}
}
