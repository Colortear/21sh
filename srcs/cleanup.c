/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:05:47 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/17 13:40:00 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

void	cleanup(t_shell *shell, t_history *hist)
{
	t_history	*prev_tmp;

	end_termcap();
	while (hist != NULL)
	{
		prev_tmp = hist->prev;
		free(hist->cmd);
		free(hist);
		hist = prev_tmp;
	}
	shell->path = freetwod(shell->path);
	if (shell)
		free(shell);
	clear_env();
}

char	**freetwod(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
	return (str);
}

void	delete_return(t_history **hist)
{
	int	i;

	i = (*hist)->y_max;
	while (i > 0)
	{
		LINE;
		DEL_LINE;
		UP;
		i--;
	}
}

void	destroy_copy(t_history *copy)
{
	while (copy && copy->next)
		copy = copy->next;
	while (copy && copy->prev)
	{
		copy->cmd ? free(copy->cmd) : 0;
		copy = copy->prev;
		copy->next ? free(copy->next) : 0;
	}
	if (copy && copy->cmd)
		free(copy->cmd);
	free(copy);
	copy = NULL;
}
