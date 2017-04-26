/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:23:51 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/25 22:11:02 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

void		exit_shell(t_history *hist, t_shell *shell, int err_code)
{
	free(hist);
	free(shell);
	exit(err_code);
}

int			main(void)
{
	t_shell		*shell;
	t_history	*hist;

	shell = (t_shell *)malloc(sizeof(t_shell));
	hist = (t_history *)malloc(sizeof(t_history));
	hist->prev = NULL;
	shell->hist_head = NULL;
	shell->path = NULL;
	if (set_termcap(shell) < 0)
		exit_shell(hist, shell, 1);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		hist = setup(shell, hist);
		hist = read_and_parse(shell, hist);
		ft_putstr("\n\r");
		if (hist->cmd && command(hist) == 1)
			break ;
	}
	cleanup(shell, hist);
	return (0);
}
