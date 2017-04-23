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
	char		character;
	static int	quote = 0;

	if (!read(fd, &character, 1))
		return (0);
	if (character == 34 && quote == 1)
		quote = 0;
	else if (character == 44 && quote == 2)
		quote = 0;
	else if (character == 34 && quote == 0)
		quote = 1;
	else if (character == 44 && quote == 0)
		quote = 2;
	else if (character == 13 && quote == 0)
		return (0);
	return (character);
}
