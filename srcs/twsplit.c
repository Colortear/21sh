/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twsplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 19:56:21 by wdebs             #+#    #+#             */
/*   Updated: 2017/06/18 17:51:09 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

char	**twsplit(char *str)
{
	int		i;
	char	**new;
	char	delimit;

	i = 0;
	new = NULL;
	delimit = ' ';
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != 34 &&
				str[i] != 39 && str[i] != 96)
		{
			delimit = i ? str[i - 1] : ' ';
			new = extract_cmd(str, new, &i, delimit);
		}
		else
			i++;
	}
	return (new);
}

char	**extract_cmd(char *str, char **new, int *i, char delimit)
{
	int		j;
	int		k;
	int		size;
	char	**tmp;

	j = 0;
	k = 0;
	size = *i;
	if (*i && str[*i] == delimit && (*i)++)
		return (new);
	tmp = new ? ft_realloc2(new) : ft_tdnew(1);
	while (tmp && tmp[j] != 0)
		j++;
	while (str[size] && str[size] != delimit)
		size++;
	tmp[j] = ft_strnew(size - *i);
	while (*i < size)
	{
		tmp[j][k] = str[*i];
		k++;
		(*i)++;
	}
	return (tmp);
}
