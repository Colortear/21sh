/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:36:35 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/03 16:39:56 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

t_history	*init_hist(t_shell *shell, t_history *hist)
{
	static int	start = 0;
	t_history	*newnode;

	if (hist->prev == NULL && start == 0)
		start = 1;
	else if (hist->cmd)
	{
		newnode = (t_history *)malloc(sizeof(t_history));
		hist->next = newnode;
		newnode->prev = hist;
		hist = newnode;
	}
	hist->chars = 0;
	shell->hist_head = hist;
	hist->next = NULL;
	hist->cmd = NULL;
	hist->x_max[0] = 0;
	hist->y_max = 0;
	return (hist);
}

void		puterm(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		str[i] == '\n' ? write(1, "\n\r", 2) : write(1, &str[i], 1);
}

void		history_move(t_shell *shell, t_history **hist, int dir)
{
	INSERT_MODE_ON;
	if ((*hist)->prev && dir == HISTORY_UP)
	{
		delete_return(hist);
		*hist = (*hist)->prev;
		LINE;
		DEL_LINE;
		disp_prompt();
		shell->x = (*hist)->x_max[(*hist)->y_max];
		shell->y = (*hist)->y_max;
		puterm((*hist)->cmd);
	}
	else if ((*hist)->next && dir == HISTORY_DOWN)
	{
		delete_return(hist);
		*hist = (*hist)->next;
		LINE;
		DEL_LINE;
		disp_prompt();
		shell->x = (*hist)->x_max[(*hist)->y_max];
		shell->y = (*hist)->y_max;
		puterm((*hist)->cmd);
	}
	INSRT_MODE_OFF;
}

void		fill_x(t_history **head, t_history *hist)
{
	int		i;

	i = -1;
	while (++i <= hist->y_max)
		(*head)->x_max[i] = hist->x_max[i];
	(*head)->y_max = hist->y_max;
}

t_history	*add_cmd(t_shell *shell, t_history *hist)
{
	if (hist->cmd)
	{
		shell->hist_head->cmd = ft_strdup(hist->cmd);
		fill_x(&shell->hist_head, hist);
	}
	return (shell->hist_head);
}
