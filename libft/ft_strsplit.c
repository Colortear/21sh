/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 17:23:06 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/17 13:27:51 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	wordc(char const *str, char x)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == x)
			i++;
		if (str[i] != x && str[i] != '\0')
			count++;
		while (str[i] != x && str[i] != '\0')
			i++;
	}
	return (count);
}

static int	wordl(char const *str, char x)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] == x)
		i++;
	while (str[i] != x && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	if (!s || (str = (char**)malloc(sizeof(char*) * (wordc(s, c) + 1))) == 0)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < wordc(s, c))
	{
		k = 0;
		if ((str[i] = (char*)malloc(sizeof(char) * wordl(&s[j], c) + 1)) == 0)
			return (NULL);
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j] != '\0')
			str[i][k++] = s[j++];
		str[i][k] = '\0';
	}
	str[i] = NULL;
	return (str);
}
