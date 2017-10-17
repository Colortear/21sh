/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip_range.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 17:11:51 by aphan             #+#    #+#             */
/*   Updated: 2017/02/28 14:30:57 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strip(char *str, int start, int end)
{
	int		j;
	char	*new;

	j = 0;
	new = NULL;
	while (start < end + 1)
	{
		new[j] = str[start];
		j++;
		start++;
	}
	return (new);
}

char		*ft_strip_range(char *str, int min, int max)
{
	int		i;
	int		len;

	i = 0;
	if (!str)
		return (str);
	len = ft_strlen(str) - 1;
	while (len > -1 && i <= len)
	{
		if (str[i] > min && str[i] < max)
			i++;
		if (str[len] > min && str[len] < max)
			len--;
	}
	return (ft_strip(str, i, len));
}
