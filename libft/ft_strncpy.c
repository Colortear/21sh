/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 12:45:22 by wdebs             #+#    #+#             */
/*   Updated: 2016/09/25 23:24:21 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		if (src[i] == '\0')
		{
			while (i < len)
			{
				dst[i] = '\0';
				i++;
			}
		}
	}
	return (dst);
}
