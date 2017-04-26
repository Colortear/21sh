/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twsplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 19:56:21 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/25 22:12:12 by wdebs            ###   ########.fr       */
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
				str[i] == 40 || str[i] == 91 || str[i] == 123)
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

	j = 0;
	k = 0;
	size = *i;
	quote = check_expansions(str[*i]);
	new = ft_realloc2(new);
	while (new && new[j])
		j++;
	while (str[size] == quote)
		size++;
	while (str[size] && str[size] != quote)
		size++;
	new[j] = ft_strnew(size - *i);
	while (++(*i) < size)
	{
		new[j][k] = str[*i];
		k++;
	}
	while (str[*i] == quote)
		(*i)++;
	return (new);
}

char	**extract_cmd(char *str, char **new, int *i)
{
	int		j;
	int		k;
	int		size;

	j = 0;
	k = 0;
	size = *i;
	new = ft_realloc2(new);
	while (new && new[j] != 0)
		j++;
	while (str[size] && str[size] != ' ' && str[size] != '\t')
		size++;
	new[j] = ft_strnew(size - *i);
	while (*i < size)
	{
		new[j][k] = str[*i];
		k++;
		(*i)++;
	}
	return (new);
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
