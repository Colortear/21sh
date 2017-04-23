/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 19:32:15 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/03 16:40:16 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

void	insert_char(char *c, t_shell *shell, t_history *hist)
{
	INSERT_MODE_ON;
	if (*c == 13)
	{
		hist->cmd = ft_insrtchar(hist->cmd, hist->chars + shell->x, '\n');
		write(1, "\n", 1);
		hist->x_max[shell->y]++;
		hist->y_max++;
		hist->chars = hist->chars + shell->x + 1;
		shell->y = hist->y_max;
		shell->x = 0;
		hist->x_max[hist->y_max] = 0;
	}
	else
	{
		hist->cmd = ft_insrtchar(hist->cmd, hist->chars + shell->x, *c);
		shell->x++;
		hist->x_max[shell->y]++;
	}
	ft_putchar(*c);
	INSRT_MODE_OFF;
}

void	delete_char(t_shell *shell, t_history **hist)
{
	int		size;

	size = (*hist)->cmd ? ft_strlen((*hist)->cmd) : 0;
	if (size > 0 && (*hist)->x_max[shell->y] > 0 && shell->x > 0)
	{
		shell->x--;
		(*hist)->x_max[shell->y]--;
		(*hist)->cmd = ft_delchar((*hist)->cmd, shell->x);
		LEFT;
		DEL_CHAR;
	}
}
