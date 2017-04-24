/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:31:13 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/22 17:17:59 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

int		openfile(char *file, int redir)
{
	if (redir == RIGHT_REDIR)
		return (open(file, O_WRONLY | O_TRUNC | O_CREAT, 0600));
	else if (redir == RIGHT_DOUBLE)
		return (open(file, O_WRONLY | O_APPEND | O_CREAT, 0600));
	else if (redir == LEFT_REDIR)
		return (open(file, O_RDONLY));
	return (0);
}

static void	duplications(t_cmd *cmds)
{
	int		fd;
	int		i;

	fd = 0;
	i = -1;
	while (cmds->out && cmds->out[++i] &&
			(fd = openfile(cmds->out[i], RIGHT_REDIR)))
		if (!cmds->out_ord && dup2(fd, 1) != -1)
			close(fd);
	i = -1;
	while (cmds->in && cmds->in[++i] &&
			(fd = openfile(cmds->in[i], LEFT_REDIR)))
		if (!cmds->in_ord && dup2(fd, 0) != -1)
			close(fd);
	i = -1;
	while (cmds->append && cmds->append[++i] &&
			(fd = openfile(cmds->append[i], RIGHT_DOUBLE)))
		if (cmds->out_ord && dup2(fd, 0) != -1)
			close(fd);
	i = -1;
	while (cmds->heredoc && cmds->heredoc[++i] &&
			(fd = openfile(cmds->heredoc[i], LEFT_DOUBLE)))
			if (cmds->in_ord && dup2(fd, 1) != -1)
			close(fd);
}

static int	path_cmd(char **cmd, int check)
{
	char		**paths;
	int			i;
	char		*tmp;
	struct stat	st;

	i = -1;
	check = 0;
	paths = ft_strsplit(getenv("PATH"), ':');
	while (paths[++i] && !check)
	{
		tmp = ft_strnew(ft_strlen(paths[i]) + ft_strlen(*cmd) + 1);
		ft_strcpy(tmp, paths[i]);
		ft_strcat(tmp, "/");
		tmp = ft_strcat(tmp, *cmd);
		if (stat(tmp, &st) > -1 && (check = 1))
		{
			free(*cmd);
			*cmd = ft_strdup(tmp);
		}
		tmp ? free(tmp) : 0;
	}
	return (check);
}

int		check_cmds(char **cmd)
{
	int		type;
	int		check;

	type = 0;
	check = 0;
	if (!ft_strcmp(*cmd, "echo") || !ft_strcmp(*cmd, "cd") || 
			!ft_strcmp(*cmd, "setenv") || !ft_strcmp(*cmd, "unsetenv")
			|| !ft_strcmp(*cmd, "env"))
		type = BIN;
	else if (!ft_strncmp(*cmd, "./", 2) || !ft_strncmp(*cmd, "../", 3))
		type = LOCAL;
	else if (ft_strcmp(*cmd, "exit") && path_cmd(cmd, check))
		type = PATH;
	return (type);
}

void	run_execs(t_cmd *cmds)
{
	int		bin;
	int		in;
	int		out;
	t_cmd	*tmp;

	bin = 1;
	in = dup(0);
	out = dup(1);
	tmp = cmds;
	while (cmds && bin && (bin = check_cmds(&cmds->cmd)) != 0)
	{
		duplications(cmds);
		if (exec(cmds, bin) == -1)
			bin = 0;
		tmp = cmds;
		cmds = next_cmd(cmds);
	}
	dup2(in, 0);
	dup2(out, 1);
	if (!bin && (cmds = tmp) && ft_strcmp(tmp->cmd, "exit") &&
			write(1, "21sh: bad command ", 18))
	{
		ft_putstr(tmp->cmd);
		ft_putstr("\n\r");
	}
}
