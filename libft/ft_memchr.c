/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 16:49:13 by wdebs             #+#    #+#             */
/*   Updated: 2016/10/01 00:38:03 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	const char		*new_s;

	i = 0;
	new_s = (const char *)s;
	while (i < n)
	{
		if (new_s[i] == (char)c)
			return ((void *)&new_s[i]);
		i++;
	}
	return (0);
}
