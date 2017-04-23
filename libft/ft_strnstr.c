/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:19:22 by wdebs             #+#    #+#             */
/*   Updated: 2016/09/25 21:57:07 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	finish;

	i = 0;
	j = 0;
	while (little[i] != '\0')
		i++;
	if (i == 0)
		return ((char *)big);
	while (big[j] != '\0' && j < len)
	{
		start = j;
		finish = 0;
		while (big[start] == little[finish] && start < len)
		{
			start++;
			finish++;
			if (finish == i)
				return ((char *)big + j);
		}
		j++;
	}
	return (0);
}
