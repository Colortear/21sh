/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 22:07:45 by wdebs             #+#    #+#             */
/*   Updated: 2017/06/18 18:57:33 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

t_cmd	*next_cmd(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	cmds = cmds->next;
	if (cmds)
	{
		cmds->std_in = tmp->std_in;
		cmds->std_out = tmp->std_out;
	}
	return (cmds);
}

int		run_builtins(t_cmd *cmds)
{
	int		ret;

	ret = 0;
	if (!ft_strcmp(cmds->cmd, "echo") && (ret = 1))
		run_echo(cmds->args);
	else if (!ft_strcmp(cmds->cmd, "cd") && (ret = 1))
		run_cd(cmds->args);
	else if (!ft_strcmp(cmds->cmd, "setenv") && cmds->args &&
			cmds->args[1] && cmds->args[2] && (ret = 1))
		ft_setenv(cmds->args[1], cmds->args[2]);
	else if (!ft_strcmp(cmds->cmd, "unsetenv") && cmds->args &&
			cmds->args[1] && (ret = 1))
		ft_unsetenv(cmds->args[1]);
	else if (!ft_strcmp(cmds->cmd, "env") && (ret = 1))
		run_env();
	return (ret);
}

void	save_fd(int io)
{
	static int	in = 0;
	static int	out = 1;
	static int	err = 2;

	if (!io)
	{
		in = dup(0);
		out = dup(1);
		err = dup(2);
	}
	else
	{
		dup2(in, 0);
		dup2(out, 1);
		dup2(err, 2);
	}
}
