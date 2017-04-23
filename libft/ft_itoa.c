/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 17:54:28 by wdebs             #+#    #+#             */
/*   Updated: 2016/10/01 03:46:36 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		length(int n)
{
	int i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int		i;
	char	*str;

	i = length(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (n == -2147483648)
		return (str = ft_strdup("-2147483648"));
	if (str != NULL)
	{
		str[0] = '0';
		str[i] = '\0';
		if (n < 0)
		{
			n = n * -1;
			str[0] = '-';
		}
		while (n != 0)
		{
			str[--i] = n % 10 + '0';
			n = n / 10;
		}
		return (str);
	}
	else
		return (NULL);
}
