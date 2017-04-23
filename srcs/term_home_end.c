/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_home_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:35:25 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/03 16:40:55 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

int		check_home_end(char *str, int check, t_shell *shell, t_history **hist)
{
	char	*home;
	char	*end;

	home = HOME_KEY;
	end = END_KEY;
	if (ft_strcmp(str, home) == 0 && (check = 1) && shell->x > 0)
		while (shell->x > 0 && shell->x--)
			LEFT;
	if (ft_strcmp(str, end) == 0 && (check = 1) && shell->x <
		(*hist)->x_max[shell->y])
	{
		while (shell->x < (*hist)->x_max[shell->y])
		{
			shell->x++;
			RIGHT;
		}
	}
	return (check);
}
