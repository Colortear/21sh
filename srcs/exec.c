/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:31:13 by wdebs             #+#    #+#             */
/*   Updated: 2017/08/11 16:04:55 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

int			openfile(char *file, int redir)
{
	int			fd;
	struct stat	st;

	fd = 0;
	if (redir == RIGHT_REDIR)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	else if (redir == RIGHT_DOUBLE)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0600);
	else if (redir == LEFT_REDIR && (fd = lstat(file, &st)) != -1)
		fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("21sh: File does not exist: ");
		ft_putstr(file);
		write(1, "\r\n", 2);
	}
	return (fd);
}

static int	duplications(t_cmd *cmds)
{
	int		fd;
	int		i;

	fd = 0;
	i = -1;
	while (fd != -1 && cmds->heredoc && cmds->heredoc[++i])
		if (!cmds->heredoc[i + 1] && cmds->in_ord == 1 &&
				(fd = heredoc(cmds, cmds->heredoc[i])) && dup2(fd, 0) != -1)
			close(fd);
	i = -1;
	while (fd != -1 && cmds->out && cmds->out[++i] &&
			(fd = openfile(cmds->out[i], RIGHT_REDIR)))
		if (cmds->out_ord == 2 && dup2(fd, 1) != -1)
			close(fd);
	i = -1;
	while (fd != -1 && cmds->append && cmds->append[++i] &&
			(fd = openfile(cmds->append[i], RIGHT_DOUBLE)))
		if (cmds->out_ord == 1 && dup2(fd, 1) != -1)
			close(fd);
	i = -1;
	while (cmds->in && cmds->in[++i] &&
			(fd = openfile(cmds->in[i], LEFT_REDIR)) != -1)
		if (cmds->in_ord == 2 && dup2(fd, 0) != -1)
			close(fd);
	return (fd);
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
	while (paths && paths[++i] && !check)
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
	paths ? freetwod(paths) : 0;
	return (check);
}

int			check_cmds(char **cmd)
{
	int		type;
	int		check;

	type = 0;
	check = 0;
	if (!ft_strcmp(*cmd, "echo") || !ft_strcmp(*cmd, "cd") ||
			!ft_strcmp(*cmd, "setenv") || !ft_strcmp(*cmd, "unsetenv")
			|| !ft_strcmp(*cmd, "env"))
		type = BIN;
	else if (!ft_strncmp(*cmd, "./", 2) || !ft_strncmp(*cmd, "../", 3)
			|| !ft_strncmp(*cmd, "/", 1))
		type = LOCAL;
	else if (ft_strcmp(*cmd, "exit") && path_cmd(cmd, check))
		type = PATH;
	return (type);
}

void		run_execs(t_cmd *cmds)
{
	t_cmd	*head;
	int		bin;

	bin = 1;
	head = cmds;
	save_fd(0);
	while (cmds && bin && (bin = check_cmds(&cmds->cmd)) != 0)
	{
		if (duplications(cmds) == -1 && (bin = 0))
			break ;
		cmds->aggs ? check_aggs(cmds->aggs) : 0;
		cmds = next_cmd(cmds);
	}
	if (cmds && !bin && ft_strcmp(cmds->cmd, "exit"))
		write(1, "21sh: bad command\n\r", 19);
	else if ((cmds = head) && bin > 1 && ft_strcmp("cd", cmds->cmd) &&
			ft_strcmp("setenv", cmds->cmd) && ft_strcmp("unsetenv", cmds->cmd))
		lay_pipe(cmds);
	else
		run_builtins(cmds);
	save_fd(1);
}
