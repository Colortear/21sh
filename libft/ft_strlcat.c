/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 19:44:16 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/13 17:04:04 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		len;
	char		*dstref;
	const char	*srcref;
	size_t		n;

	dstref = dst;
	srcref = src;
	n = size;
	while (*dstref != '\0' && n-- != 0)
		dstref++;
	len = dstref - dst;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(srcref));
	while (*srcref != '\0')
	{
		if (n != 1)
		{
			*dstref++ = *srcref;
			n--;
		}
		srcref++;
	}
	*dstref = '\0';
	return (len + (srcref - src));
}
