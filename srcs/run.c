/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 22:07:45 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/28 20:23:50 by wdebs            ###   ########.fr       */
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

void	run(t_cmd *cmds, int fd[2], int bin, int fd_in)
{
	extern char	**environ;

	signal(SIGINT, SIG_DFL);
	if (cmds->next)
	{
		dup2(fd[1], 1);
		close(fd[0]);
	}
	if (bin == BIN)
	{
		run_builtins(cmds);
		exit(1);
	}
	else if (!access(cmds->cmd, R_OK || X_OK))
	{
		dup2(fd_in, 0);
		execve(cmds->cmd, cmds->args, environ);
	}
	else
	{
		ft_putstr("\n\r21sh: Permission denied: ");
		ft_putstr(cmds->cmd);
		ft_putstr("\n\r");
		exit(-1);
	}
}

int		exec(t_cmd *cmds, int bin)
{
	int			fd[2];
	int			ret;
	pid_t		pid;
	static int	fd_in = 0;
	int			status;

	ret = cmds->next ? pipe(fd) : 0;
	if (!ft_strcmp(cmds->cmd, "cd") || !ft_strcmp(cmds->cmd, "setenv") ||
			!ft_strcmp(cmds->cmd, "unsetenv"))
		run_builtins(cmds);
	else if ((pid = fork()) == (pid_t) 0)
		run(cmds, fd, bin, fd_in);
	else if (pid < (pid_t) 0)
		ret = -1;
	else
	{
		waitpid(-1, &status, 0);
		ret >= 0 ? close(fd[1]) : 0;
		fd_in = ret >= 0 ? fd[0] : 0;
	}
	return (ret);
}

void	run_builtins(t_cmd *cmds)
{
	if (!ft_strcmp(cmds->cmd, "echo"))
		run_echo(cmds->args);
	else if (!ft_strcmp(cmds->cmd, "cd"))
		run_cd(cmds->args);
	else if (!ft_strcmp(cmds->cmd, "setenv") && cmds->args)
		ft_setenv(cmds->args[0], cmds->args[1]);
	else if (!ft_strcmp(cmds->cmd, "unsetenv") && cmds->args)
		ft_unsetenv(cmds->args[0]);
	else if (!ft_strcmp(cmds->cmd, "env"))
		run_env();
}
