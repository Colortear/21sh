/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:40:23 by wdebs             #+#    #+#             */
/*   Updated: 2017/03/15 22:52:49 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		command(t_shell *shell)
{
	if (ft_strcmp(shell->cmd, "exit") == 0)
		return (1);
	return (0);
}

void	read_and_parse(t_shell *shell)
{
	char	c;

	while ((c = ft_getchar_mod(0, &shell->cmd)))
		if (terms_esc(c, shell) == 0 && ((c > 8 && c < 14)
					|| (c > 31 && c < 127)))
			insert_char(&c);
	add_to_history(shell);
}
