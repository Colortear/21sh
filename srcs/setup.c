/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:36:22 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/22 17:07:04 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

void		disp_prompt(void)
{
	char	*home_path;
	size_t	home_len;
	char	*current;

	current = NULL;
	home_path = getenv("HOME");
	home_len = ft_strlen(home_path);
	current = getcwd(NULL, 0);
	if (ft_strncmp(home_path, current, home_len) == 0)
	{
		ft_putchar('~');
		ft_putstr(current + home_len);
	}
	else
		ft_putstr(current);
	ft_putstr(" $ ");
	free(current);
}

t_history	*setup(t_shell *shell, t_history *hist)
{
	disp_prompt();
	shell->x = 0;
	shell->path = shell->path ? freetwod(shell->path) : 0;
	shell->path = ft_strsplit(getenv("PATH"), ':');
	hist = init_hist(shell, hist);
	return (hist);
}
