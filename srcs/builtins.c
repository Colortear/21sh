/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 00:21:55 by wdebs             #+#    #+#             */
/*   Updated: 2017/08/11 14:33:07 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

void	run_env(void)
{
	extern char	**environ;
	int			i;

	i = -1;
	while (environ[++i])
	{
		ft_putstr(environ[i]);
		ft_putstr("\n\r");
	}
}

void	run_echo(char **args)
{
	char		*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	while (args[++i])
	{
		if (args[i][0] == '$' && (tmp = getenv(args[i] + 1)))
			ft_putstr(tmp);
		else
			ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		tmp = NULL;
	}
	write(1, "\n\r", 2);
}

void	run_cd(char **path)
{
	char	*copy;
	int		check;

	copy = NULL;
	check = 0;
	if (ft_twodlen(path) > 2 && (check = 1))
		ft_putstr("cd: too many arguments\n\r");
	else if (path[1] && path[1][0] == '-' && !path[1][1] && (check = 1))
		chdir(getenv("OLDPWD"));
	ft_setenv("OLDPWD", getcwd(NULL, 0));
	if (path && path[1] && check == 0)
	{
		copy = path[1][0] == '~' ? ft_strjoin(getenv("HOME"), path[1]) :
			ft_strdup(path[1]);
		if (chdir(copy) < 0)
			ft_putstr("cd: no such file or directory\n\r");
	}
	else if (path && path[0] && check == 0)
		chdir(getenv("HOME"));
	copy ? free(copy) : 0;
}
