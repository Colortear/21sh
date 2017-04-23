/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:38:39 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/22 19:56:27 by wdebs            ###   ########.fr       */
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
	int i = 0;

	len = commands_length(type, *cmds);
	if (type == RIGHT_REDIR && ft_realloc2((*cmds)->out) &&
			((*cmds)->out_ord = 0))
		(*cmds)->out[len] = ft_strdup(tmp);
	else if (type == LEFT_REDIR && ft_realloc2((*cmds)->in) &&
			((*cmds)->in_ord = 0))
		(*cmds)->in[len] = ft_strdup(tmp);
	else if (type == RIGHT_DOUBLE && ft_realloc2((*cmds)->append) &&
			((*cmds)->out_ord = 1))
		(*cmds)->append[len] = ft_strdup(tmp);
	else if (type == LEFT_DOUBLE && ft_realloc2((*cmds)->heredoc) &&
			((*cmds)->in_ord = 1))
		(*cmds)->heredoc[len] = ft_strdup(tmp);
	else if (type == AMPERSAND && ft_realloc2((*cmds)->aggs))
		(*cmds)->aggs[len] = ft_strdup(tmp);
	else if (type == NORMAL && ft_realloc2((*cmds)->args))
		(*cmds)->args[len] = ft_strdup(tmp);
	while ((*cmds)->args[i]) {
		ft_putstr("args[");
		ft_putnbr(i);
		ft_putstr("] is: ");
		ft_putstr((*cmds)->args[i]);
		write(1, " ", 1);
		i++;
	}
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
		add_file_type(cmds, type, tmp);
	}
	return (len);
}

int			parse_pipes(char *str)
{
	int		i;
	char	**piped;
	char	**cmds;
	int		check;
	t_cmd	*commands;

	i = -1;
	check = 0;
	piped = ft_strsplit(str, '|');
	cmds = NULL;
	commands = NULL;
	while (piped[++i] && check == 0)
	{
		commands = link_cmds(commands);
		cmds = twsplit(piped[i]);
		commands->cmd = cmds ? ft_strdup(cmds[i]) : NULL;
		if (cmds && commands->cmd && ft_realloc2(commands->args))
			commands->args[0] = ft_strdup(cmds[0]);
		if (cmds && redirections(cmds, &commands) == -1)
			check = -1;
		cmds ? freetwod(cmds) : 0;
	}
	check == 0 ? run_execs(commands->head) : 0;
	commands ? free_cmds(commands) : 0;
	return (check);
}
