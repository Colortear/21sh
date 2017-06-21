/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:30:28 by wdebs             #+#    #+#             */
/*   Updated: 2017/05/03 18:06:52 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_unsetenv(const char *name)
{
	char		**copy;
	extern char	**environ;
	int			j;
	int			len;
	char		*temp;

	len = 0;
	j = 0;
	temp = ft_strtrim(name);
	while (environ && environ[len])
		len++;
	copy = (char **)ft_memalloc(sizeof(char *) * (len + 2));
	len = -1;
	while (environ[++len])
		if (ft_strlcmp(environ[len], temp, ft_strlen(temp)))
			copy[j++] = environ[len];
	environ = copy;
	return (0);
}
