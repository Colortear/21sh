/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar_mod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:11:49 by wdebs             #+#    #+#             */
/*   Updated: 2017/03/15 23:40:06 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_getchar_mod(int fd, char **line)
{
	char	*tmp;
	char	character;
	int		size;

	if (!read(fd, &character, 1) || character == 13)
			return (0);
	if (character < 32 || character > 126)
		return (character);
	size = *line ? ft_strlen(*line) : 0;
	tmp = ft_strnew(size + 1);
	if (*line)
		ft_strcpy(tmp, *line);
	tmp[size] = character;
	if (*line)
		free(*line);
	*line = tmp;
	return (character);
}
