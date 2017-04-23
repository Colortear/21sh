/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:55:19 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/03 15:55:23 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_delchar(char *str, int place)
{
	char	*tmp;
	int		size;
	int		j;
	int		i;

	i = 0;
	j = 0;
	size = ft_strlen(str) - 1;
	tmp = ft_strnew(size);
	while (str[i] != '\0')
	{
		if (i != place)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	free(str);
	return (tmp);
}
