/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:40:23 by wdebs             #+#    #+#             */
/*   Updated: 2017/05/01 21:57:37 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

int			check_commands(char *str)
{
	if (check_spaces(str) == 0)
		return (0);
	if (parse_pipes(str) == -1)
		return (1);
	return (0);
}

int			command(t_history *hist)
{
	char	**parsed_cmd;
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	parsed_cmd = ft_strsplit(hist->cmd, ';');
	while (parsed_cmd && parsed_cmd[i] &&
			(ret = check_commands(parsed_cmd[i])) == 0)
		i++;
	freetwod(parsed_cmd);
	return (ret);
}

t_history	*copy_history(t_history *hist)
{
	t_history	*copy;
	t_history	*head;
	t_history	*tmp;

	copy = (t_history *)malloc(sizeof(t_history));
	head = copy;
	copy->next = NULL;
	copy->prev = NULL;
	while (hist)
	{
		fill_x(&copy, hist);
		copy->y_max = hist->y_max;
		copy->chars = hist->chars;
		copy->cmd = hist->cmd ? ft_strdup(hist->cmd) : NULL;
		if (hist->prev)
		{
			copy->prev = (t_history *)malloc(sizeof(t_history));
			tmp = copy;
			copy = copy->prev;
			copy->next = tmp;
			copy->prev = NULL;
		}
		hist = hist->prev;
	}
	return (head);
}

t_history	*read_and_parse(t_shell *shell, t_history *hist)
{
	int			check;
	char		c;
	t_history	*hist_copy;

	check = 0;
	hist_copy = copy_history(hist);
	while (check != -1 && (c = ft_getchar_mod(0)))
		if ((check = terms_esc(c, shell, &hist_copy)) == 0 &&
				((c > 9 && c < 14) || c == 4 || (c > 31 && c < 127)))
			insert_char(&c, shell, hist_copy);
	if (hist_copy->cmd)
		hist = add_cmd(shell, hist_copy);
	hist->d = check == -1 ? 1 : 0;
	destroy_copy(hist_copy);
	return (hist);
}

int			check_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}
