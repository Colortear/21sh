/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 20:08:08 by wdebs             #+#    #+#             */
/*   Updated: 2017/06/13 22:39:46 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

static void	set_read(int *lpipe)
{
	dup2(lpipe[0], STDIN_FILENO);
	close(lpipe[0]);
	close(lpipe[1]);
}

static void	set_write(int *rpipe)
{
	dup2(rpipe[1], STDOUT_FILENO);
	close(rpipe[0]);
	close(rpipe[1]);
}

static void	fork_and_chain(t_cmd *cmds, int *lpipe, int *rpipe)
{
	extern char	**environ;
	pid_t		pid;
	int			exe;

	exe = 0;
	if ((pid = fork()) == 0)
	{
		if (lpipe)
			set_read(lpipe);
		if (rpipe)
			set_write(rpipe);
		if (!run_builtins(cmds) && !access(cmds->cmd, R_OK || X_OK))
		{
			execve(cmds->cmd, cmds->args, environ);
			write(1, "HERE\n\r", 6);
		}
		else
		{
			exe ? write(1, "21sh: permission denied\r\n", 25) : 0;
			exit(1);
		}
	}
	else if (pid == -1)
		write(1, "21sh: something bad happened\r\n", 30);
}

void		lay_pipe(t_cmd *cmds)
{
	int		lpipe[2];
	int		rpipe[2];

	pipe(rpipe);
	fork_and_chain(cmds, NULL, rpipe);
	lpipe[0] = rpipe[0];
	lpipe[1] = rpipe[1];
	while (cmds->next)
	{
		pipe(rpipe);
		fork_and_chain(cmds, lpipe, rpipe);
		close(lpipe[0]);
		close(lpipe[1]);
		lpipe[0] = rpipe[0];
		lpipe[1] = rpipe[1];
		cmds = cmds->next;
	}
	fork_and_chain(cmds, lpipe, NULL);
	close(lpipe[0]);
	close(lpipe[1]);
	waitpid(-1, NULL, 0);
}