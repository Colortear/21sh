/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 20:20:56 by wdebs             #+#    #+#             */
/*   Updated: 2016/09/29 23:03:16 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	new_c;
	unsigned char	*new_b;

	i = 0;
	new_b = (unsigned char *)b;
	new_c = (unsigned char)c;
	while (i < len)
	{
		new_b[i] = new_c;
		i++;
	}
	return (b);
}
