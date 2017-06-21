/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:32:19 by wdebs             #+#    #+#             */
/*   Updated: 2017/02/28 17:31:31 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_line(char *line)
{
	extern char	**environ;
	char		**new;
	int			len;

	len = 0;
	while (environ && environ[len])
		len++;
	new = (char **)ft_memalloc(sizeof(char *) * (len + 2));
	len = -1;
	while (environ[++len])
		new[len] = environ[len];
	new[len] = line;
	new[len + 1] = 0;
	environ = new;
}

int			ft_setenv(const char *name, const char *value)
{
	extern char	**environ;
	char		*line;
	char		*env;
	int			i;

	i = -1;
	line = ft_strjoin(name, "=");
	env = line;
	line = ft_strjoin(line, value);
	free(env);
	while (environ && environ[++i])
	{
		if (!ft_strlcmp(environ[i], name, ft_strlen(name)))
		{
			env = environ[i];
			environ[i] = line;
			return (0);
		}
	}
	add_line(line);
	return (0);
}
