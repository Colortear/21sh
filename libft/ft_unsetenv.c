/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:30:28 by wdebs             #+#    #+#             */
/*   Updated: 2017/02/28 17:28:00 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_unsetenv(const char *name)
{
	extern char	**environ;
	char		**ep;
	char		**sp;
	size_t		len;

	len = ft_strlen(name);
	ep = environ;
	sp = ep;
	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL)
		return (-1);
	while (*ep != NULL )
	{

		if (ft_strncmp(*ep, name, len) == 0 && (*ep)[len] == '=')
		{
			while (*sp != NULL)
			{
				*sp = *(sp + 1);
				sp++;
			}
		}
		else
			ep++;
	}
	return (0);
}
