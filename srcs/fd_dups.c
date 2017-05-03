/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 22:23:02 by wdebs             #+#    #+#             */
/*   Updated: 2017/05/03 00:03:57 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

int		isnum(char *tmp, int size)
{
	int		ret;
	int		i;

	i = 0;
	ret = 1;
	while (i < size && ret)
	{
		if (tmp[i] < '0' || tmp[i] > '9')
			ret = 0;
		i++;
	}
	return (ret);
}

void	fd_dups(char **split)
{
	int		dir;

	dir = 0;
	if (split[0][ft_strlen(split[0]) - 1] == '>')
		dir = 1;
	else if (split[0][ft_strlen(split[0]) - 1] == '<')
		dir = 2;
	if (dir == 2 && !ft_strcmp(split[1], "-") &&
			isnum(split[0], ft_strlen(split[0]) - 1))
		close(ft_atoi(split[0]));
	else if (dir == 1 && !ft_strcmp(split[0], "-") &&
			isnum(split[1], ft_strlen(split[1]) - 1))
		close(ft_atoi(split[1]));
	else if (dir == 1 && isnum(split[0], ft_strlen(split[0]) - 1) &&
			isnum(split[1], ft_strlen(split[1]) - 1))
		dup2(ft_atoi(split[1]), ft_atoi(split[0]));
	else if (dir == 2 && isnum(split[0], ft_strlen(split[0]) - 1) &&
			isnum(split[1], ft_strlen(split[1]) - 1))
		dup2(ft_atoi(split[0]), ft_atoi(split[1]));
}

void	check_aggs(char **aggs)
{
	char	**split;
	int		i;

	i = 0;
	split = NULL;
	while (aggs[i])
	{
		if (ft_strchr(aggs[i], '>') || ft_strchr(aggs[i], '<'))
			split = ft_strsplit(aggs[i], '&');
		if (split)
			fd_dups(split);
		split ? freetwod(split) : 0;
		i++;
	}
}
