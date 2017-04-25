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

char	ft_getchar_mod(int fd)
{
	char		c;
	static char	quote = 0;

	if (!read(fd, &c, 1))
		return (0);
	if (quote == 0 && (c == 34 || c == 39 || c == 96 ||
				c == 40 || c == 91 || c == 123))
		quote = c;
	else if (quote && c == quote && (c == 34 || c == 39 || c == 96))
		quote = 0;
	else if (quote && (quote == 40 || quote == 91 || quote == 123) &&
				(c == 41 || c == 93 || c == 125))
		quote = 0;
	else if (c == 13 && quote == 0)
		return (0);
	return (c);
}
