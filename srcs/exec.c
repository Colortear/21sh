/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:31:13 by wdebs             #+#    #+#             */
/*   Updated: 2017/03/15 22:52:34 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*void	run(t_vars *vars, char ***envp)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!access(vars->args[0], R_OK || X_OK))
	{
		pid = fork();
		if (pid)
			waitpid(-1, &status, 0);
		else
			execve(vars->args[0], vars->args, *(envp));
	}
	else
	{
		ft_putstr("minishell: Permission denied: ");
		ft_putendl(vars->args[0]);
	}
}*/
