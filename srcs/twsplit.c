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

	i = 0;
	new = NULL;
	while (str && str[i])
	{
		if (str[i] == 34 || str[i] == 39 || str[i] == 96 ||
				str[i] == '(' || str[i] == '[' || str[i] == '{')
			new = split_quotes(str, new, &i);
		else if (str[i] != ' ' && str[i] != '\t')
			new = extract_cmd(str, new, &i);
		else
			i++;
	}
	return (new);
}

char	**split_quotes(char *str, char **new, int *i)
{
	char	quote;
	int		j;
	int		k;
	int		size;
	char	**tmp;

	j = 0;
	k = -1;
	size = *i;
	quote = check_expansions(str[*i]);
	tmp = new ? ft_realloc2(new) : ft_tdnew(1);
	while (tmp && tmp[j])
		j++;
	while (str[size] == quote)
		size++;
	while (str[size] && str[size] != quote)
		size++;
	tmp[j] = ft_strnew(size - *i);
	while (++(*i) < size)
		tmp[j][++k] = str[*i];
	while (str[*i] == quote)
		(*i)++;
	return (tmp);
}

char	**extract_cmd(char *str, char **new, int *i)
{
	int		j;
	int		k;
	int		size;
	char	**tmp;

	j = 0;
	k = 0;
	size = *i;
	tmp = new ? ft_realloc2(new) : ft_tdnew(1);
	while (tmp && tmp[j] != 0)
		j++;
	while (str[size] && str[size] != ' ' && str[size] != '\t')
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

char	check_expansions(char exp)
{
	if (exp == 40)
		exp = 41;
	else if (exp == 91)
		exp = 93;
	else if (exp == 123)
		exp = 125;
	return (exp);
}
