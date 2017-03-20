/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 22:54:30 by wdebs             #+#    #+#             */
/*   Updated: 2017/02/22 01:12:48 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(len + 1);
	if (new_str != NULL)
	{
		while (s1[i] != '\0')
			new_str[j++] = s1[i++];
		i = 0;
		while (s2[i] != '\0')
			new_str[j++] = s2[i++];
		new_str[j] = '\0';
		return (new_str);
	}
	else
		return (NULL);
}
