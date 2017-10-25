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

static int	reload(char *mod)
{
	t_stack	*s;
	int		i;
	int		ret;

	s = new_stack();
	i = 0;
	while (mod[i])
	{
		if (!is_empty(s) && mod[i] == peek(s))
			pop(s);
		else if (mod[i] == 34 || mod[i] == 39 || mod[i] == 96)
			push(s, mod[i]);
		i++;
	}
	ret = s->size;
	del_stack(s);
	return (ret);
}

char		ft_getchar_mod(int fd, char *mod)
{
	char		c;
	static int	quote = 0;

	if (mod)
		quote = reload(mod);
	if (!read(fd, &c, 1))
		return (0);
	else if (c == 13 && !quote)
		c = 0;
	return (c);
}
