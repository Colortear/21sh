/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 21:12:07 by wdebs             #+#    #+#             */
/*   Updated: 2017/05/01 22:26:35 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

t_cmd	*link_cmds(t_cmd *cmds)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmds)
	{
		new->prev = cmds;
		cmds->next = new;
		new->head = cmds->head;
		new->next = NULL;
	}
	else
	{
		new->prev = NULL;
		new->next = NULL;
		new->head = new;
	}
	new->aggs = NULL;
	new->in = NULL;
	new->out = NULL;
	new->heredoc = NULL;
	new->append = NULL;
	new->cmd = NULL;
	new->hds = NULL;
	new->args = ft_tdnew(1);
	return (new);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds->aggs ? freetwod(cmds->aggs) : 0;
		cmds->in ? freetwod(cmds->in) : 0;
		cmds->out ? freetwod(cmds->out) : 0;
		cmds->append ? freetwod(cmds->append) : 0;
		cmds->heredoc ? freetwod(cmds->heredoc) : 0;
		cmds->cmd ? free(cmds->cmd) : 0;
		cmds->args ? freetwod(cmds->args) : 0;
		cmds->hds ? free(cmds->hds) : 0;
		cmds = cmds->next;
		free(tmp);
	}
	free(cmds);
}
