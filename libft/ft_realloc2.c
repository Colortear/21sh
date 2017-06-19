/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:59:29 by wdebs             #+#    #+#             */
/*   Updated: 2017/06/18 17:27:02 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc2(char **arr)
{
	char	**new;
	int		size;
	int		i;
	int		j;

	size = 0;
	i = -1;
	j = -1;
	while (arr && arr[size])
		size++;
	new = ft_tdnew(size + 1);
	new[size + 1] = 0;
	new[size] = 0;
	while (arr && arr[++i] != 0)
		new[i] = ft_strdup(arr[i]);
	while (arr && arr[++j])
		free(arr[j]);
	free(arr);
	return (new);
}
