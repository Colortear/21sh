/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 19:50:18 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/28 21:09:48 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

static void	input(char **hd, char *key, int check)
{
	char	*new;
	char	*tmp;
	int		ret;

	while (1)
	{
		write(1, "> ", 2);
		if (check && (new = ft_strjoin(*hd, "\n")))
		{
			free(*hd);
			*hd = new;
		}
		if (!(ret = get_next_line(0, &tmp)) || !ft_strcmp(tmp, key))
			break ;
		new = (!check) ? ft_strdup(tmp) : ft_strjoin(*hd, tmp);
		free(*hd);
		free(tmp);
		*hd = new;
		check = 1;
	}
	if (!ret)
		write(1, "Input interrupted by end-of-transmission signal.\n", 49);
	free(tmp);
}

int			heredoc(t_cmd *cmds, char *key)
{
	int	fd;

	end_termcap();
	input(&cmds->hds, key, 0);
//	set_termcap(0);
	fd = open("/tmp/hd", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd && cmds->hds)
		write(fd, cmds->hds, ft_strlen(cmds->hds));
	close(fd);
	fd = open("/tmp/hd", O_RDONLY);
	return (fd);
}
