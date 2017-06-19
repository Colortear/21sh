/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:36:22 by wdebs             #+#    #+#             */
/*   Updated: 2017/06/18 18:37:38 by wdebs            ###   ########.fr       */
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
	home_len = home_path ? ft_strlen(home_path) : 0;
	current = getcwd(NULL, 0);
	if (home_len && ft_strlen(current) >= home_len &&
			ft_strncmp(home_path, current, home_len) == 0)
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
