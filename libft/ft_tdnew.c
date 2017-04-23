/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tdnew.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:04:26 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/14 20:23:18 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tdnew(int size)
{
	char	**new;
	int		i;

	i = -1;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	while (++i <= size)
		new[i] = 0;
	return (new);
}
