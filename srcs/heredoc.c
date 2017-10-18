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

/*char	heredoc_manage(char *key, int len)
{
	char		c;
	static int	check = 0;

	c = 0;
	read(0, &c, 1);
	if ((c > 9 && c < 14) || (c > 31 && c < 127))
		write(1, &c, 1);
	if (c == 13)
		write(1, "\n", 1);
	if (check == len && c == 13)
		c = -1;
	else if (c == key[check])
		check++;
	else
		check = 0;
	return (c);
}

int		heredoc(t_cmd *cmds, char *key)
{
	char	c;
	char	buf[10000];
	int		i;
	int		len;
	int		fd;

	fd = 0;
	cmds->hds = NULL;
	len = ft_strlen(key);
	i = -1;
	while ((c = heredoc_manage(key, len)) > -1)
	{
		if (c > 0 && c != 13)
			buf[++i] = c;
		else if (c > 0 && c == 13)
			buf[++i] = '\n';
	}
	buf[i - len] = 0;
	if (i > -1)
		cmds->hds = ft_strdup(buf);
	fd = open("/tmp/hd", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	fd ? write(fd, cmds->hds, ft_strlen(cmds->hds)) : 0;
	close(fd);
	fd = open("/tmp/hd", O_RDONLY);
	return (fd);
}*/

static char	*input(char *key)
{
	char	*hd;
	char	*new;
	char	*tmp;
	int		check;

	check = 0;
	hd = NULL;
	while (write(1, ">", 1))
	{
		if (check)
		{
			new = ft_strjoin(hd, "\n");
			free(hd);
			hd = new;
		}
		if (!get_next_line(0, &tmp) || !ft_strcmp(tmp, key))
			break ;
		new = (!check) ? ft_strdup(tmp) : ft_strjoin(hd, tmp);
		free(hd);
		free(tmp);
		hd = new;
		check = 1;
	}
	free(tmp);
	return (hd);
}


int		heredoc(t_cmd *cmds, char *key)
{
	int	fd;

	end_termcap();
	cmds->hds = input(key);
	set_termcap();
	fd = open("/tmp/hd", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	fd ? write(fd, cmds->hds, ft_strlen(cmds->hds)) : 0;
	close(fd);
	fd = open("/tmp/hd", O_RDONLY);
	return (fd);
}
