/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:38:39 by wdebs             #+#    #+#             */
/*   Updated: 2017/05/03 19:34:50 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

int			commands_length(int type, t_cmd *cmds)
{
	int		len;

	len = 0;
	if (cmds->out && type == RIGHT_REDIR)
		len = ft_twodlen(cmds->out);
	else if (cmds->in && type == LEFT_REDIR)
		len = ft_twodlen(cmds->in);
	else if (cmds->append && type == RIGHT_DOUBLE)
		len = ft_twodlen(cmds->append);
	else if (cmds->heredoc && type == LEFT_DOUBLE)
		len = ft_twodlen(cmds->heredoc);
	else if (cmds->aggs && type == AMPERSAND)
		len = ft_twodlen(cmds->aggs);
	else if (cmds->args && type == NORMAL)
		len = ft_twodlen(cmds->args);
	return (len);
}

void		add_file_type(t_cmd **cmds, int type, char *tmp)
{
	int		len;

	len = commands_length(type, *cmds);
	if (type == RIGHT_REDIR && ((*cmds)->out = ft_realloc2((*cmds)->out)) &&
			((*cmds)->out_ord = 2))
		(*cmds)->out[len] = ft_strdup(tmp);
	else if (type == LEFT_REDIR && ((*cmds)->in = ft_realloc2((*cmds)->in)) &&
			((*cmds)->in_ord = 2))
		(*cmds)->in[len] = ft_strdup(tmp);
	else if (type == RIGHT_DOUBLE &&
			((*cmds)->append = ft_realloc2((*cmds)->append)) &&
			((*cmds)->out_ord = 1))
		(*cmds)->append[len] = ft_strdup(tmp);
	else if (type == LEFT_DOUBLE &&
			((*cmds)->heredoc = ft_realloc2((*cmds)->heredoc)) &&
			((*cmds)->in_ord = 1))
		(*cmds)->heredoc[len] = ft_strdup(tmp);
	else if (type == AMPERSAND && ((*cmds)->aggs = ft_realloc2((*cmds)->aggs)))
		(*cmds)->aggs[len] = ft_strdup(tmp);
	else if (type == NORMAL && ((*cmds)->args = ft_realloc2((*cmds)->args)))
		(*cmds)->args[len] = ft_strdup(tmp);
}

static int	redirections(char **cmd, t_cmd **cmds)
{
	int		i;
	int		len;
	int		type;
	char	*tmp;

	i = 0;
	ft_strcmp(cmd[i], "exit") == 0 ? len = -1 : 0;
	while (cmd[++i] && len != -1)
	{
		tmp = NULL;
		if (ft_strcmp(cmd[i], ">") == 0 && (type = RIGHT_REDIR))
			tmp = cmd[++i];
		else if (ft_strcmp(cmd[i], "<") == 0 && (type = LEFT_REDIR))
			tmp = cmd[++i];
		else if (ft_strcmp(cmd[i], ">>") == 0 && (type = RIGHT_DOUBLE))
			tmp = cmd[++i];
		else if (ft_strcmp(cmd[i], "<<") == 0 && (type = LEFT_DOUBLE))
			tmp = cmd[++i];
		else if (ft_strchr(cmd[i], '&') && (type = AMPERSAND))
			tmp = cmd[i];
		else if ((type = NORMAL))
			tmp = cmd[i];
		tmp ? add_file_type(cmds, type, tmp) : 0;
	}
	return (len);
}

int			parse_pipes(char *str)
{
	int		i;
	char	**piped;
	char	**cmds;
	int		check;
	t_cmd	*c;

	i = -1;
	check = 0;
	piped = ft_strsplit(str, '|');
	c = NULL;
	cmds = NULL;
	while (piped[++i] && check_spaces(piped[i]) && check == 0)
	{
		c = link_cmds(c);
		cmds = twsplit(piped[i]);
		c->cmd = cmds ? ft_strdup(cmds[0]) : NULL;
		c->cmd ? c->args[0] = ft_strdup(cmds[0]) : NULL;
		if (cmds && redirections(cmds, &c) == -1)
			check = -1;
		cmds ? freetwod(cmds) : 0;
	}
	check == 0 ? run_execs(c->head) : 0;
	c ? free_cmds(c->head) : 0;
	piped ? freetwod(piped) : 0;
	return (check);
}
