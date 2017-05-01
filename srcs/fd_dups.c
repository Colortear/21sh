#include "twsh.h"

int		ampersand_type(char **amp)
{
	int		type;
	int		len;

	type = 0;
	len = ft_strlen(amp[0]);
	if (amp[0][len - 1] == '<')
		type = AMP_LEFT;
	else if (amp[0][len] - 1 == '>')
		type = AMP_RIGHT;
	else
		ft_putstr("Need redirection instruction before ampersand");
	return (type);
}

void	amp(char **tmp, int type)
{
	int		fd_left;
	int		fd_right;
	char	buf[10000];

	fd_left = type == AMP_LEFT ? AMP_LEFT : AMP_RIGHT;
	fd_right = 0;
	if (isnum(tmp[0], ft_strlen(tmp[0]) - 1))
		fd_left = ft_atoi(ft_strncpy(buf, tmp[0], ft_strlen(tmp[0]) - 1));
	else
		fd_left = open(ft_strncpy(buf, tmp[0], ft_strlen(tmp[0]) - 1), O_RDONLY);
	if (isnum(tmp[1], ft_strlen(tmp[1])))
		fd_right = read(ft_atoi(tmp[1]), NULL, 0) > -1 ? ft_atoi(tmp[1]) : -1;
	else if (ft_strcmp(tmp[1], "-"))
		fd_right = open(tmp[1], O_RDONLY, 0600);
	if (fd_right == -1)
		ft_putstr("Bad file decriptor\n\r");
	else
	{
		if (!ft_strcmp(tmp[1], "-"))
			close(fd_left);
		else
			fd_left = dup(fd_right);
	}
}

int		isnum(char *tmp, int size)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (!ret && i < size)
	{
		if (tmp[i] <= '0' || tmp[i] >= '9')
			ret = 1;
		i++;
	}
	return (ret);
}

void	ampersand(t_cmd *cmds)
{
	int		i;
	int		len;
	char	**tmp;
	int		type;

	i = -1;
	len = 0;
	type = 0;
	tmp = NULL;
	while (cmds->aggs[++i])
	{
		tmp = ft_strsplit(cmds->aggs[i],'&');
		if ((len = ft_twodlen(tmp)) != 2)
			ft_putstr("Incorrect formatting for fd duplication\n\r");
		else
			type = ampersand_type(tmp);
		if (tmp && type)
			amp(tmp, type);
		tmp ? free(tmp) : 0;
		tmp = NULL;
	}
}
