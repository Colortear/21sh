/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insrtchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:55:09 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/03 15:55:13 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_insrtchar(char *str, int place, char c)
{
	char	*tmp;
	int		size;

	size = str ? ft_strlen(str) + 1 : 1;
	tmp = ft_strnew(size);
	ft_strncpy(tmp, str, place);
	tmp[place] = c;
	str ? ft_strlcat(tmp, str + place, size + 1) : 0;
	str ? free(str) : 0;
	return (tmp);
}
